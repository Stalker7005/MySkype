#pragma once
#include <memory>

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
    void Reserve(std::uint64_t size);
    void Dispose();

public:
    void SetData(const char* data, std::uint64_t size);
    char* GetData() const;
    std::uint64_t Size() const;

private:
    void ClearData();

private:
    std::uint64_t m_blobSize;
    std::uint64_t m_dataSize;
    std::unique_ptr<char[]> m_data;

private:
    static const std::uint64_t DefaultBlobSize;

};
}