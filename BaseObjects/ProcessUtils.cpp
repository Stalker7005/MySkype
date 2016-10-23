#include "ProcessUtils.h"
#include <windows.h>

#ifdef BUILD_WINDOWS
#include <windows.h>
#elif BUILD_LINUX
//TODO
#endif

std::uint64_t ProcessUtils::GetProcessId()
{
    auto processId = std::uint64_t();
#ifdef BUILD_WINDOWS
    processId = GetCurrentProcessId();
#elif BUILD_LINUX

#endif
    return processId;
}

fs::path ProcessUtils::GetExecutablePath()
{
    auto name = std::wstring();
    auto buf = std::vector<TCHAR>();
    auto bufSize = 4096;

    buf.resize(bufSize);

#ifdef BUILD_WINDOWS
    auto bytes = GetModuleFileName(NULL, &buf[0], bufSize);
#elif BUILD_LINUX

#endif
    return fs::path(buf.begin(), buf.end());
}

fs::path ProcessUtils::GetExecutableFolderPath(const fs::path& path)
{
    auto result = fs::path();
    boost::system::error_code code;
    if (!path.empty() && path.has_parent_path())
    {
        result = path.parent_path();
    }

    return result;
}

fs::path ProcessUtils::GetLoggerFolder()
{
    return fs::path("Logs");
}

std::wstring ProcessUtils::GetExecutableName(const fs::path& path)
{
    auto result = std::wstring();
    if (!path.empty() && path.has_filename())
    {
        result = path.filename().generic_wstring();
    }

    return result;
}

