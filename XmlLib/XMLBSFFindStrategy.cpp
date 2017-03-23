#include "XMLBSFFindStrategy.h"
#include <queue>

namespace XML {
std::shared_ptr<XMLElement> XMLBSFFindStrategy::FindElement(tinyxml2::XMLElement* firstElement, const std::string& name)
{
    std::deque<tinyxml2::XMLElement*> m_elements;
    for (auto node = firstElement; node; node = node->NextSiblingElement())
    {
        m_elements.emplace_back(node);
        while (!m_elements.empty())
        {
            auto internalNode = m_elements.front();
            m_elements.pop_front();
            for (auto element = internalNode->FirstChildElement(); element; element = element->NextSiblingElement())
            {
                auto elementName = element->Name();
                if (elementName)
                {
                    if (std::strcmp(elementName, name.c_str()) == 0)
                    {
                        return std::make_shared<XMLElement>(element);
                    }
                    else
                    {
                        m_elements.emplace_back(element);
                    }
                }
            }
        }
    }

    return nullptr;
}
}

