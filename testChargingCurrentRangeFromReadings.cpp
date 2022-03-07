#define CATCH_CONFIG_MAIN
#include "test-framework/catch.hpp"

TEST_CASE("test charging current incidents in reading") {
    int chargingCurrentSamples[] = {4, 5};
    std::string expectedOutput = "4-5, 2";
    REQUIRE(getCurrentIncidentsFromReadings(chargingCurrentSamples) == expectedOutput);
}