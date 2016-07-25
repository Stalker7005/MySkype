#pragma once
#include <sstream>

namespace BaseObjects {
class Blob
{
public:
    Blob();
    ~Blob();

public:
    void Clear();
    std::stringstream& GetStream();
    const char* GetCString();
    std::string GetString();

private:
    std::stringstream m_buffer;
};
}