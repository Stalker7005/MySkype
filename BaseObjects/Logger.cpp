#include "Logger.h"

#include <boost/format.hpp>
#include <log4cplus/configurator.h>
#include <log4cplus/appender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include "FileUtils.h"
#include "ProcessUtils.h"

#include <mutex>

const std::string Logger::Pattern = "%d{%m/%d/%y %H:%M:%S:%Q} [%p]: %m %n";
const std::uint32_t Logger::LogSize = 5 * 1024 * 1024;
const std::uint32_t Logger::PreallocatedBufferSize = 256;

Logger& Logger::GetIntance()
{
    static Logger logger;

    return logger;
}

void Logger::Init(const std::wstring& fileName /*= L""*/)
{
    std::lock_guard<std::mutex> initGuard(m_logMutex);

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

    m_isInited = true;

    log4cplus::initialize();
    log4cplus::helpers::SharedObjectPtr<log4cplus::Appender>
        appender(new log4cplus::RollingFileAppender(LOG4CPLUS_STRING_TO_TSTRING(fullLogPath.wstring()), LogSize, 5));

    appender->setName(LOG4CPLUS_C_STR_TO_TSTRING("LoggerAppender"));
    
    std::auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(LOG4CPLUS_STRING_TO_TSTRING(Pattern)));
    appender->setLayout(layout);
    auto rootLogger = log4cplus::Logger::getRoot();
    rootLogger.addAppender(appender);
}

void Logger::Log(Type type, std::int64_t line, const char* functionName, const char* format, ...)
{
    std::lock_guard<std::mutex> logGuard(m_logMutex);

    va_list args;
    va_start(args, format);
    auto ret = std::int32_t();

    while (true)
    {
        ret = vsnprintf(m_buffer.get(), m_bufSize, format, args);
        if (ret < 0)
        {
            m_bufSize *= 2;
            m_buffer = std::make_unique<char[]>(m_bufSize);
        }
        else if (ret < m_bufSize)
        {
            //We allocate valid buffer
            break;
        }
    }
    va_end(args);

    auto resultMsg = boost::str(boost::format("[%2%:%1%]") % line % functionName) + m_buffer.get();

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
    }
}

Logger::Logger():
m_isInited(false),
m_buffer(std::make_unique<char[]>(PreallocatedBufferSize)),
m_loggerName(std::to_wstring(ProcessUtils::GetProcessId())),
m_bufSize(PreallocatedBufferSize)
{}

Logger::~Logger()
{}

