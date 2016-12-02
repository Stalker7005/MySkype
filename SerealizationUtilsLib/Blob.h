#pragma once
#include <memory>

#include <cstdint>
#include <cstring>

namespace Serialization{
class Blob
{
public:
    Blob();
    explicit Blob(std::uint64_t size);
    Blob(const void* data, std::uint64_t size);
    ~Blob() = default;

public:
    Blob(const Blob& blob);
    Blob& operator=(const Blob& blob);
    Blob(Blob&& blob);
    Blob& operator=(Blob&& blob);
    bool operator==(const Blob& blob);
    bool operator!=(const Blob& blob);
    explicit operator bool();

public:
    void Resize(std::uint64_t size, bool saveData = false);
    void Dispose();

public:
    void SetData(const void* data, std::uint64_t size);
    std::uint8_t* GetData() const;
    std::uint64_t Size() const;

private:
    void ClearData();

private:
    std::uint64_t m_blobSize;
    std::uint64_t m_dataSize;
    std::unique_ptr<std::uint8_t[]> m_data;

private:
    static const std::uint64_t DefaultBlobSize;

};
}