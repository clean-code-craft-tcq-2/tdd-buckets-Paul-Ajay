#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "chargingCurrentRangeFromReadings.h"

TEST_CASE("test charging current incidents in reading") {
    std::vector<int> chargingCurrentSamples = {4, 5};
    std::string expectedOutput = "4-5, 2";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);
}