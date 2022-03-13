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
    std::map<std::string, int> inputMap = {{"1-2", 1}}; 
    REQUIRE(toCsvFormat(inputMap) == "Range, Readings\n1-2, 1");
}

TEST_CASE("test case for checking isValidChargingCurrentSamples") {
    std::vector<int> chargingCurrentSamples = {4,5};
    REQUIRE(isValidChargingCurrentSamples(chargingCurrentSamples) == true);
    chargingCurrentSamples = {-4,5};
    REQUIRE(isValidChargingCurrentSamples(chargingCurrentSamples) == false);
}

TEST_CASE("test case for charging sample with single input") {
    std::vector<int> chargingCurrentSamples = {4};
    std::string expectedOutput = "Range, Readings\n4-4, 1";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);
}

TEST_CASE("test case for charging sample with 2 input") {
    std::vector<int> chargingCurrentSamples = {4,5};
    std::string expectedOutput = "Range, Readings\n4-5, 2";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);    
}

TEST_CASE("test case for charging sample with more samples") {
    std::vector<int> chargingCurrentSamples = {4,5,5,9,9,10,11};
    std::string expectedOutput = "Range, Readings\n4-5, 3\n9-11, 4";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);      
}

TEST_CASE("test case for charging sample with no continuous readings") {
    std::vector<int> chargingCurrentSamples = {4,7,9};
    std::string expectedOutput = "Range, Readings\n4-4, 1\n7-7, 1\n9-9, 1";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput); 
}