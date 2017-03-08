#pragma once

#include <string>
#include <cstdint>
#include <mutex>
#include <memory>
#include <cstdint>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/layout.h>
#include <mutex>

class Logger
{
public:
    enum class Type
    {
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        Trace
    };

    enum class LogLevel
    {
        ALL,
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Fatal,
        NoLog
    };

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void SetConsoleOut(bool useConsole);
    void SetLogFilterLevel(LogLevel level);

public:
    void Init(const std::wstring& fileName = L"", bool consoleOut = false, LogLevel level = LogLevel::ALL);
    void Log(Type type, std::int64_t line, const char* functionName, const char* format, ...);
    static Logger& GetIntance();

private:
    Logger();
    ~Logger();

private:
    std::uint64_t m_bufSize;
    std::wstring m_loggerName;

private:
    static const std::string Pattern;
    static const std::string ConsoleAppenderName;
    static const std::string Debug32AppenderName;
    static const std::uint32_t LogSize;
    static const std::uint32_t PreallocatedBufferSize;
};

#define LOGGER Logger::GetIntance()
#define LOG_INIT LOGGER.Init
#define LOG_DEB(format, ...) LOGGER.Log(Logger::Type::Debug, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) LOGGER.Log(Logger::Type::Info,  __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) LOGGER.Log(Logger::Type::Warning, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERR(format, ...) LOGGER.Log(Logger::Type::Error, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) LOGGER.Log(Logger::Type::Fatal, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_TRACE(format, ...) LOGGER.Log(Logger::Type::Trace, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

