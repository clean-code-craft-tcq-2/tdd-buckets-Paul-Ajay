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

TEST_CASE("test case for getNumberFromVector function"){
    std::vector<int> inputVector = {1,1,4,6};
    int expectedOutput = 1146;
    REQUIRE(getNumberFromVector(inputVector) == expectedOutput);
    inputVector = {-1, 0};
    expectedOutput = -10;
    REQUIRE(getNumberFromVector(inputVector) == expectedOutput);  
}

TEST_CASE("test case for getCurrentFromADCReading function") {
    // current adc value with value in range
    std::vector<int> adcValues = {1,1,4,6};
    int adcMaximumValue = 4094;
    int expectedOutput = 3;
    int maximumCurrentValue = 10;
    int minimumCurrentValue = 0;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
    // current adc value with out of limit returns error (minimum value -1)
    adcValues = {4,0,9,5};
    expectedOutput = minimumCurrentValue -1;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
    adcValues = {-1};
    expectedOutput = minimumCurrentValue -1;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);

    adcMaximumValue = 1022;
    maximumCurrentValue = 15;
    minimumCurrentValue = -15;
    adcValues = {5,1,1};
    expectedOutput = 0;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
    adcValues = {9,2,0};
    expectedOutput = 12;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
    adcValues = {1,0,2};
    expectedOutput = -12;
    REQUIRE(getCurrentFromADCReading(adcValues, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
}

TEST_CASE("test case for convertADCCurrentReadingsToInteger function") {
    std::vector<std::vector<int>> chargingCurrentSamples = {{1,6,3,7},{2,0,4,7}};
    int adcMaximumValue = 4094;
    int maximumCurrentValue = 10;
    int minimumCurrentValue = 0;
    std::vector<int> expectedOutput = {4,5};
    REQUIRE(convertADCCurrentReadingsToInteger(chargingCurrentSamples, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
    chargingCurrentSamples = {{-1,0},{2,0,4,7}};
    expectedOutput = {-1,5};
    REQUIRE(convertADCCurrentReadingsToInteger(chargingCurrentSamples, adcMaximumValue, maximumCurrentValue, minimumCurrentValue) == expectedOutput);
}

TEST_CASE("test case for getADCMaximumValueFromRange function") {
    int adcRange = 12;
    int expectedOutput = 4094;
    REQUIRE(getADCMaximumValueFromRange(adcRange) == expectedOutput);
}

TEST_CASE("test case for getCurrentIncidentsFromReadings function") {
    GIVEN("charging sample with 1 continuous reading") {
        std::vector<std::vector<int>> chargingCurrentSamples = {{1,6,3,7},{2,0,4,7}};
        int adcRange = 12;
        int maximumCurrentValue = 10;
        int minimumCurrentValue = 0;
        WHEN("getCurrentIncidentsFromReadings() is called with input array") {
            std::string expectedOutput = "Range, Readings\n4-5, 2";
            std::string outputFromFunction = getCurrentIncidentsFromReadings(chargingCurrentSamples, adcRange, maximumCurrentValue, minimumCurrentValue, *consolePrint);
            THEN("output in CSV format is generated") {
                REQUIRE(outputFromFunction == expectedOutput);
            }
        }
    }
    GIVEN("charging sample with -ve element") {
        std::vector<std::vector<int>> chargingCurrentSamples = {{-1,0},{2,0,4,7}};
        int adcRange = 12;
        int maximumCurrentValue = 10;
        int minimumCurrentValue = 0;
        WHEN("getCurrentIncidentsFromReadings() is called with input array") {
            std::string expectedOutput = "";
            std::string outputFromFunction = getCurrentIncidentsFromReadings(chargingCurrentSamples, adcRange, maximumCurrentValue, minimumCurrentValue, *consolePrint);
            THEN("empty string corresponding to error case occurred") {
                REQUIRE(outputFromFunction == expectedOutput);
            }
        }
    }

    GIVEN("charging sample with unsorted array and adc range from -ve to +ve value") {
        int adcRange = 10;
        int maximumCurrentValue = 15;
        int minimumCurrentValue = -15;
        std::vector<std::vector<int>> chargingCurrentSamples = {{8,5,2},{6,4,7}, {6,8,1},{8,1,8},{1,0,2},{1,7,0},{4,0,8},{0},{1,0,2,2},{8,8,6}}; // {10,4,5,9,-12,-10,-3,-15,15,11}        
        WHEN("getCurrentIncidentsFromReadings() is called with input array") {
            std::string expectedOutput = "Range, Readings\n15-15, 2\n3-5, 3\n9-12, 5";
            std::string outputFromFunction = getCurrentIncidentsFromReadings(chargingCurrentSamples, adcRange, maximumCurrentValue, minimumCurrentValue, *consolePrint);
            THEN("output in CSV format is generated") {
                REQUIRE(outputFromFunction == expectedOutput);
            }
        }
    }
}