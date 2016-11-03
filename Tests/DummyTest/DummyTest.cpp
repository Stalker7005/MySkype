#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

int sum(int a, int b)
{
    return a + b;
}
TEST_CASE("Dummy first test") {

    int a = 10;
    int b = 20;
    
    REQUIRE(sum(a, b) == 30);
    REQUIRE(sum(a, b) == 20);
}