#pragma once
#include <memory>
#include "XMLElement.h"

namespace XML {
class XMLFindStrategy
{
public:
    virtual std::shared_ptr<XMLElement> FindElement(tinyxml2::XMLElement* firstElement, const std::string& name) = 0;
};
}

