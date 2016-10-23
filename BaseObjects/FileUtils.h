#pragma once
#include <string>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

class FileUtils
{
public:
    static bool CreateFolder(const fs::path& dirPath);
};

