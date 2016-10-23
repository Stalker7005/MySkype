#include "FileUtils.h"
#include <vector>
#include "Logger.h"
#include <boost/filesystem.hpp>


bool FileUtils::CreateFolder(const fs::path& dirPath)
{ 
    auto isCreated = false;
    if (!fs::exists(dirPath))
    {
        boost::system::error_code err;
         isCreated = fs::create_directory(dirPath, err);
        fs::permissions(dirPath, fs::all_all);
    }
    
    return isCreated;
}
