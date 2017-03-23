#pragma once
#include "tinyxml2.h"
#include <string>
#include <memory>
#include "XMLElement.h"
#include "XMLFindStrategy.h"

namespace XML {
class XMLDocument
{
public:
    XMLDocument();
    XMLDocument(const std::string& docName);
    ~XMLDocument();

public:
    XMLDocument(const XMLDocument& doc) = delete;
    XMLDocument& operator=(const XMLDocument& doc) = delete;

public:
    bool Load(const std::string& name);
    bool Save(const std::string& name);
    bool Parse(const std::string& text);

public:
    std::shared_ptr<XMLElement> FindElement(const std::string& name);
    std::shared_ptr<XMLElement> FindElement(const std::shared_ptr<XMLElement>& element, const std::string& name);

public:
    void SetFindStrategy(std::unique_ptr<XMLFindStrategy> strategy);
    tinyxml2::XMLDocument* GetNative();

private:
    bool Validate(tinyxml2::XMLError error);

private:
    tinyxml2::XMLDocument m_xmlDoc;
    std::unique_ptr<XMLFindStrategy> m_findStrategy;

};

}

