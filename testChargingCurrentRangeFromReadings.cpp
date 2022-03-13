#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "chargingCurrentRangeFromReadings.h"

TEST_CASE("test case for checking isContinuousNumbers function") {
    REQUIRE(isContinuousNumbers(1,2) == true);
    REQUIRE(isContinuousNumbers(2,4) == false);
}

TEST_CASE("test case for checking formatRangeString function") {
    REQUIRE(formatRangeString(1,2) == "1-2");
}

TEST_CASE("test case for checking toCsvFormat function") {
    REQUIRE(toCsvFormat({"1-2, 1"}) == "Range, Readings\n1-2 ,1");
}

TEST_CASE("test case for charging sample with single input") {
    std::vector<int> chargingCurrentSamples = {4};
    std::map<std::string, int> expectedOutput = {{"4-4", 1}};
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);
}

TEST_CASE("test case for charging sample with 2 input") {
    std::vector<int> chargingCurrentSamples = {4,5};
    std::map<std::string, int> expectedOutput = {{"4-5", 2}};
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);    
}

TEST_CASE("test case for charging sample with more samples") {
    std::vector<int> chargingCurrentSamples = {4,5,5,9,9,10,11};
    std::map<std::string, int> expectedOutput = {{"4-5", 3}, {"9-11", 4}};
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);      
}

TEST_CASE("test case for charging sample with no continuous readings") {
    std::vector<int> chargingCurrentSamples = {4,7,10};
    std::map<std::string, int> expectedOutput = {{"4-4", 1}, {"7-7", 1}, {"10-10", 1}};
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput); 
}