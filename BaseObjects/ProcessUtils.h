#pragma once
#include <cstdint>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

class ProcessUtils
{
public:
    static std::uint64_t GetProcessId();
    static fs::path GetExecutablePath();
    static fs::path GetExecutableFolderPath(const fs::path& path);
    static fs::path GetLoggerFolder();
    static std::wstring GetExecutableName(const fs::path& path);
};

