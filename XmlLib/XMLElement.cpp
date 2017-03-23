#include "XMLElement.h"
#include "Logger.h"

namespace XML {

XMLElement::XMLElement(tinyxml2::XMLElement* element)
: m_element(element)
{
}


std::int32_t XMLElement::ToInt32() const
{
    auto val = std::int32_t();
    Validate(m_element->QueryIntText(&val));

    return val;
}

std::uint32_t XMLElement::ToUInt32() const
{
    auto val = std::uint32_t();
    Validate(m_element->QueryUnsignedText(&val));

    return val;
}

std::int64_t XMLElement::ToInt64() const
{
    auto val = std::int64_t();
    Validate(m_element->QueryInt64Text(&val));

    return val;
}

bool XMLElement::ToBool() const
{
    auto val = bool();
    Validate(m_element->QueryBoolText(&val));

    return val;
}

float XMLElement::ToFloat() const
{
    auto val = float();
    Validate(m_element->QueryFloatText(&val));

    return val;
}

double XMLElement::ToDouble() const
{
    auto val = double();
    m_element->QueryDoubleText(&val);

    return val;
}

std::string XMLElement::ToString() const
{
    auto str = std::string();
    auto value = m_element->GetText();
    if (value)
    {
        str = value;
    }

    return str;
}

tinyxml2::XMLElement* XMLElement::GetNative()
{
    return m_element;
}

bool XMLElement::Validate(tinyxml2::XMLError error) const
{
    if (error == tinyxml2::XML_SUCCESS)
    {
        auto val = m_element->Value();
        if (val)
        {
            LOG_ERR("Can't query element %s", val);
        }
        else
        {
            LOG_ERR("Can't query element");
        }
        
        return true;
    }

    return false;
}

}

