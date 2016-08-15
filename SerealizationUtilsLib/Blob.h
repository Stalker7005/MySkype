#pragma once
#include <memory>
#include <sstream>
#include <cstdint>
#include <cstring>

namespace Serialization{
class Blob
{
public:
    Blob();
    Blob(std::uint64_t size);
    ~Blob();

public:
    void Allocate(std::uint64_t size);
    void Clear();
    std::uint8_t* GetDataBuf();
    std::iostream& GetDataStream();
    std::uint64_t Size() const;
    

private:
    std::uint64_t m_blobSize;
    std::unique_ptr<std::uint8_t[]> m_charBuf;
    std::stringstream m_stream;
    

private:
    static const std::uint64_t DefaultBlobSize;

};
}