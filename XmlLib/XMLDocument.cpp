#include "XMLDocument.h"
#include "Logger.h"
#include <string.h>
#include <queue>
#include "XMLBSFFindStrategy.h"

namespace XML {

XMLDocument::XMLDocument()
{
    SetFindStrategy(std::make_unique<XMLBSFFindStrategy>());
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

std::shared_ptr<XMLElement> XMLDocument::FindElement(const std::string& name)
{
    return m_findStrategy->FindElement(m_xmlDoc.RootElement(), name);
}

std::shared_ptr<XMLElement> XMLDocument::FindElement(const std::shared_ptr<XMLElement>& element, const std::string& name)
{
    return m_findStrategy->FindElement(element->GetNative(), name);
}

void XMLDocument::SetFindStrategy(std::unique_ptr<XMLFindStrategy> strategy)
{
    m_findStrategy = std::move(strategy);
}

tinyxml2::XMLDocument* XMLDocument::GetNative()
{
    return &m_xmlDoc;
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


