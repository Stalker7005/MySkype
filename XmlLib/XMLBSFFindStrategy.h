#pragma once
#include "XMLFindStrategy.h"

namespace XML {
class XMLBSFFindStrategy: public XMLFindStrategy
{
public:
    virtual std::shared_ptr<XMLElement> FindElement(tinyxml2::XMLElement* firstElement, const std::string& name) override;

};
}

