#include "Logger.h"

#include <boost/format.hpp>
#include <log4cplus/configurator.h>
#include <log4cplus/appender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/win32debugappender.h>
#include "FileUtils.h"
#include "ProcessUtils.h"

#include <mutex>

const std::string Logger::Pattern = "%d{%m/%d/%y %H:%M:%S:%Q} [%p]: %m %n";
const std::string Logger::ConsoleAppenderName = "Console";
const std::string Logger::Debug32AppenderName = "Win32Debug";
const std::uint32_t Logger::LogSize = 5 * 1024 * 1024;
const std::uint32_t Logger::PreallocatedBufferSize = 256;

Logger& Logger::GetIntance()
{
    static Logger logger;

    return logger;
}

void Logger::SetConsoleOut(bool useConsole)
{
    auto root = log4cplus::Logger::getRoot();

    auto consoleAppender = root.getAppender(LOG4CPLUS_C_STR_TO_TSTRING(ConsoleAppenderName));
    if (consoleAppender)
    {
        if (!useConsole)
        {
            root.removeAppender(LOG4CPLUS_C_STR_TO_TSTRING(ConsoleAppenderName));
        }
    }
    else
    {
        if (useConsole)
        {
            log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender());
            consoleAppender->setName(LOG4CPLUS_C_STR_TO_TSTRING(ConsoleAppenderName));
            consoleAppender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(LOG4CPLUS_C_STR_TO_TSTRING(Pattern))));
            root.addAppender(consoleAppender);
        }
    }
}

void Logger::SetLogFilterLevel(LogLevel level)
{
    auto currentLogger = log4cplus::Logger::getInstance(m_loggerName);
    switch (level)
    {
    case Logger::LogLevel::ALL:
        currentLogger.setLogLevel(log4cplus::ALL_LOG_LEVEL);
        break;
    case Logger::LogLevel::Trace:
        currentLogger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
        break;
    case Logger::LogLevel::Debug:
        currentLogger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
        break;
    case Logger::LogLevel::Info:
        currentLogger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
        break;
    case Logger::LogLevel::Warn:
        currentLogger.setLogLevel(log4cplus::WARN_LOG_LEVEL);
        break;
    case Logger::LogLevel::Error:
        currentLogger.setLogLevel(log4cplus::ERROR_LOG_LEVEL);
        break;
    case Logger::LogLevel::NoLog:
        currentLogger.setLogLevel(log4cplus::OFF_LOG_LEVEL);
        break;
    default:
        break;
    }
}

void Logger::Init(const std::wstring& fileName /*= L""*/, bool consoleOut /*= false*/, LogLevel level /*= LogLevel::ALL*/)
{
    auto executablePath = ProcessUtils::GetExecutablePath();
    auto logFileName = std::wstring();
    
    if (fileName.empty())
    {
        logFileName = ProcessUtils::GetExecutableName(executablePath);
    }
    else
    {
        logFileName = fileName;
    }
    
    logFileName += L".log";
    
    auto executableFolderPath = ProcessUtils::GetExecutableFolderPath(executablePath);
    auto pathLogFolder = executableFolderPath / ProcessUtils::GetLoggerFolder();
    FileUtils::CreateFolder(pathLogFolder);
    auto fullLogPath = pathLogFolder / logFileName;
    
    log4cplus::initialize();
    log4cplus::helpers::SharedObjectPtr<log4cplus::Appender>
        appender(new log4cplus::RollingFileAppender(LOG4CPLUS_STRING_TO_TSTRING(fullLogPath.wstring()), LogSize, 5));
    
    appender->setName(LOG4CPLUS_C_STR_TO_TSTRING("LoggerAppender"));
    
    std::auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(LOG4CPLUS_STRING_TO_TSTRING(Pattern)));
    appender->setLayout(layout);
    auto rootLogger = log4cplus::Logger::getRoot();
    rootLogger.addAppender(appender);

    SetConsoleOut(consoleOut);
    SetLogFilterLevel(level);
}

void Logger::Log(Type type, std::int64_t line, const char* functionName, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    auto ret = std::int32_t();

    int bufferSize = PreallocatedBufferSize;
    std::unique_ptr<char[]> buffer;
    
    bool packed = false;
    while (!packed)
    {
        buffer = std::make_unique<char[]>(bufferSize);
        buffer[bufferSize - 1] = 0;
    
        auto coded = vsnprintf(buffer.get(), bufferSize, format, args);
        if (coded >= 0)
        {
            buffer[bufferSize - 1] = 0;
            packed = true;
        }
        else
        {
            int iErrno = errno;
            if (iErrno == EILSEQ ||//character cannot be converted to ASCII (May be on MS Windows systems)
                iErrno == EINVAL)//invalid format string
            {//always ensure buffer is zero terminated
                buffer[bufferSize - 1] = 0;
                packed = true;
            }
            else
            {//seems, not enough buffer space; increasebuffer and try again
                buffer.reset();
                bufferSize += PreallocatedBufferSize;
            }
        }
    }
    va_end(args);

    auto resultMsg = boost::str(boost::format("[%2%:%1%]") % line % functionName) + buffer.get();

    auto currentLogger = log4cplus::Logger::getInstance(m_loggerName);
    switch (type)
    {
    case Logger::Type::Debug:
        LOG4CPLUS_DEBUG(currentLogger, resultMsg.c_str());
        break;
    case Logger::Type::Info:
        LOG4CPLUS_INFO(currentLogger, resultMsg.c_str());
        break;
    case Logger::Type::Warning:
        LOG4CPLUS_WARN(currentLogger, resultMsg.c_str());
        break;
    case Logger::Type::Error:
        LOG4CPLUS_ERROR(currentLogger, resultMsg.c_str());
        break;
    case Logger::Type::Trace:
        LOG4CPLUS_TRACE(currentLogger, resultMsg.c_str());
        break;
    case Logger::Type::Fatal:
        LOG4CPLUS_FATAL(currentLogger, resultMsg.c_str());
        break;
    }
}

Logger::Logger():
m_loggerName(std::to_wstring(ProcessUtils::GetProcessId())),
m_bufSize(PreallocatedBufferSize)
{
    auto root = log4cplus::Logger::getRoot();
#ifdef BUILD_WINDOWS
    {
        log4cplus::SharedAppenderPtr win32debugAppender(new log4cplus::Win32DebugAppender);
        win32debugAppender->setName(LOG4CPLUS_C_STR_TO_TSTRING(Debug32AppenderName));
        win32debugAppender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(LOG4CPLUS_C_STR_TO_TSTRING(Pattern))));
        root.addAppender(win32debugAppender);
    }
#endif
}

Logger::~Logger()
{}

