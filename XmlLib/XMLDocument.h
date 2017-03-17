#pragma once
#include "tinyxml2.h"
#include <string>

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
    
private:
    bool Validate(tinyxml2::XMLError error);

private:
    tinyxml2::XMLDocument m_xmlDoc;

};

}

