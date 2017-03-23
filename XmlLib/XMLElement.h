#pragma once
#include "tinyxml2.h"
#include <cstdint>
#include <string>

namespace XML {
class XMLElement
{
public:
    XMLElement(tinyxml2::XMLElement* element);
    ~XMLElement() = default;

public:
    std::int32_t ToInt32() const;
    std::uint32_t ToUInt32() const;
    std::int64_t ToInt64() const;
    bool ToBool() const;
    float ToFloat() const;
    double ToDouble() const;
    std::string ToString() const;
    tinyxml2::XMLElement* GetNative();

private:
    bool Validate(tinyxml2::XMLError error) const;

private:
    tinyxml2::XMLElement* m_element;

};
}

