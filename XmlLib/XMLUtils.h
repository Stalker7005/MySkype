#pragma once
#include "tinyxml2.h"

namespace XML {
class XMLUtils
{
public:
    XMLUtils(const XMLUtils& xmlUtils) = delete;
    XMLUtils& operator=(const XMLUtils& xmlUtils) = delete;

public:
    static XMLUtils& GetIntance()
    {
        static XMLUtils xml;

        return xml;
    }
    
private:
    XMLUtils();
    ~XMLUtils() = default;
};

#define XMLUTILS XMLUtils::GetInstance()
}
