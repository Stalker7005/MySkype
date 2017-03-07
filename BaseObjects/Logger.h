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
        Trace
    };

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    void Init(const std::wstring& fileName = L"");
    void Log(Type type, std::int64_t line, const char* functionName, const char* format, ...);
    static Logger& GetIntance();

private:
    Logger();
    ~Logger();

private:
    std::mutex m_logMutex;
    bool m_isInited;
    std::unique_ptr<char[]> m_buffer;
    std::uint64_t m_bufSize;
    std::wstring m_loggerName;
    std::once_flag m_initLoggerFlag;
private:
    static const std::string Pattern;
    static const std::uint32_t LogSize;
    static const std::uint32_t PreallocatedBufferSize;
};

#define LOG_INIT() Logger::GetIntance().Init()
#define LOG_INIT(fileName) Logger::GetIntance().Init(fileName);
#define LOG_DEB(format, ...) Logger::GetIntance().Log(Logger::Type::Debug, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) Logger::GetIntance().Log(Logger::Type::Info,  __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) Logger::GetIntance().Log(Logger::Type::Warning, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERR(format, ...) Logger::GetIntance().Log(Logger::Type::Error, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_TRACE(format, ...) Logger::GetIntance().Log(Logger::Type::Trace, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

