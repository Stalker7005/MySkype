#include "catch.hpp"
#include "XMLDocument.h"
#include "XMLElement.h"
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

TEST_CASE("XML")
{

    SECTION("XML")
    {
        XMLDocument* doc = new XMLDocument();
        XMLNode* element = doc->InsertEndChild(doc->NewElement("element"));

        XMLElement* sub[3] = { doc->NewElement("sub"), doc->NewElement("sub"), doc->NewElement("sub") };
        for (int i = 0; i < 3; ++i) {
            sub[i]->SetAttribute("attrib", i);
        }
        element->InsertEndChild(sub[2]);
        XMLNode* comment = element->InsertFirstChild(doc->NewComment("comment"));
        comment->SetUserData((void*)2);
        element->InsertAfterChild(comment, sub[0]);
        element->InsertAfterChild(sub[0], sub[1]);
        sub[2]->InsertFirstChild(doc->NewText("& Text!"));
        doc->Print();

        // And now deletion:
        element->DeleteChild(sub[2]);
        doc->DeleteNode(comment);

        element->FirstChildElement()->SetAttribute("attrib", true);
        element->LastChildElement()->DeleteAttribute("attrib");

        int value1 = 10;
        int value2 = doc->FirstChildElement()->LastChildElement()->IntAttribute("attrib", 10);
        int result = doc->FirstChildElement()->LastChildElement()->QueryIntAttribute("attrib", &value1);

        doc->Print();

        {
            XMLPrinter streamer;
            doc->Print(&streamer);
            printf("%s", streamer.CStr());
        }
        {
            XMLPrinter streamer(0, true);
            doc->Print(&streamer);
        }
        doc->SaveFile("./resources/out/pretty.xml");
        doc->SaveFile("./resources/out/compact.xml", true);
        delete doc;
    }
}



