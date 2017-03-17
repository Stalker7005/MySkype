#include "XMLDocument.h"
#include "Logger.h"

namespace XML {

XMLDocument::XMLDocument()
{

}

XMLDocument::~XMLDocument()
{

}

XMLDocument::XMLDocument(const std::string& docName)
{
    Load(docName);
}

bool XMLDocument::Load(const std::string& name)
{
    auto result = Validate(m_xmlDoc.LoadFile(name.c_str()));
    if (result)
    {
        LOG_INFO("Xml file with name %s downloaded succesfully", name);
    }
    else
    {
        LOG_ERR("Can't load xml file %s", name);
    }

    return result;
}

bool XMLDocument::Save(const std::string& name)
{
    auto result = Validate(m_xmlDoc.SaveFile(name.c_str()));
    if (result)
    {
        LOG_INFO("Xml file %s name saved succesfully", name);
    }
    else
    {
        LOG_ERR("Can't save xml file %s", name);
    }

    return result;
}

bool XMLDocument::Parse(const std::string& text)
{
    auto result = Validate(m_xmlDoc.Parse(text.c_str()));
    if (result)
    {
        LOG_INFO("Xml document parsed succesfully {%s}", text);
    }
    else
    {
        LOG_ERR("Can't parse document {%s}", text);
    }

    return result;
}

bool XMLDocument::Validate(tinyxml2::XMLError error)
{
    if (error == tinyxml2::XML_SUCCESS)
    {
        return true;
    }
    else
    {
        LOG_ERR("Error:%s", m_xmlDoc.ErrorIDToName(error));
        return false;
    }
}

}


