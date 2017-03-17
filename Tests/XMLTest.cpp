#include "catch.hpp"
#include "tinyxml2.h"
using namespace tinyxml2;
TEST_CASE("XML")
{

    SECTION("XML")
    {
        XMLDocument doc;
        doc.LoadFile("testXml.xml");
        auto elem1 = doc.FirstChildElement()->FirstChildElement("TestString");
        auto text = elem1->GetText();
        REQUIRE(std::strcmp(text, "Hello World") == 0);
        auto elem2 = doc.FirstChildElement()->FirstChildElement("TestInt");
        auto val = elem2->Int64Text();
        REQUIRE(val == 10);
    }
}



