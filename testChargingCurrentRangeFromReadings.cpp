#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "chargingCurrentRangeFromReadings.h"

TEST_CASE("test case for checking isContinuousNumbers function") {
    REQUIRE(isContinuousNumbers(1,2) == true);
    REQUIRE(isContinuousNumbers(2,4) == false);
}

TEST_CASE("test case for doSortVector function") {
    std::vector<int> chargingCurrentSamples = {10,4,5,9,12,10,11,3};
    std::vector<int> expectedOutput = {3,4,5,9,10,10,11,12};
    REQUIRE(doSortVector(chargingCurrentSamples) == expectedOutput);
    // test to ensure original array is not modified
    chargingCurrentSamples = {5,1,7};
    auto copyOfOriginalData = chargingCurrentSamples;
    doSortVector(chargingCurrentSamples);
    REQUIRE(copyOfOriginalData == chargingCurrentSamples);
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

TEST_CASE("test case for getCurrentRangesAndReadingsMap") {
    // charging sample with single element
    std::vector<int> chargingCurrentSamples = {4};
    std::map<std::string, int> expectedOutput = {{"4-4", 1}};
    REQUIRE(getCurrentRangesAndReadingsMap(chargingCurrentSamples) == expectedOutput);
    // charging sample with 2 elements
    chargingCurrentSamples = {4,5};
    expectedOutput = {{"4-5", 2}};
    REQUIRE(getCurrentRangesAndReadingsMap(chargingCurrentSamples) == expectedOutput);
    // charging sample with more samples
    chargingCurrentSamples = {4,5,5,9,9,10,11};
    expectedOutput = {{"4-5", 3}, {"9-11", 4}};
    REQUIRE(getCurrentRangesAndReadingsMap(chargingCurrentSamples) == expectedOutput);
    // charging sample with no continuous readings
    chargingCurrentSamples = {4,7,10};
    expectedOutput = {{"4-4", 1}, {"7-7", 1}, {"10-10", 1}};
    REQUIRE(getCurrentRangesAndReadingsMap(chargingCurrentSamples) == expectedOutput);
}

TEST_CASE("test case for getCurrentIncidentsFromReadings function") {
    // charging sample with 1 continuous reading
    std::vector<int> chargingCurrentSamples = {4,5};
    std::string expectedOutput = "Range, Readings\n4-5, 2";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples, *consolePrint) == expectedOutput);
    // charging sample with -ve element
    chargingCurrentSamples = {-4,5};
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples, *consolePrint) == "");
    // charging sample with unsorted vector
    chargingCurrentSamples = {10,4,5,9,12,10,11,3};
    expectedOutput = "Range, Readings\n3-5, 3\n9-12, 5";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples, *consolePrint) == expectedOutput);
}

TEST_CASE("test case for getCurrentFromADCReading function") {
    // current adc value with value in range
    std::vector<int> adcValues = {1,1,4,6};
    int adcMinumumValue = 0;
    int adcMaximumValue = 4094;
    int expectedOutput = 3;
    int maximumCurrentValue = 10;
    int minimumCurrentValue = 0;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMinumumValue, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
    // current adc value with out of limit returns error (minimum value -1)
    adcValues = {4,0,9,5};
    expectedOutput = minimumCurrentValue -1;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMinumumValue, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
}