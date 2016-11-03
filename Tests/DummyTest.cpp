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