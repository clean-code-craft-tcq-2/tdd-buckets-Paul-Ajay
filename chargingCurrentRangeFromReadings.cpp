#include "chargingCurrentRangeFromReadings.h"

bool isContinuousNumbers(int firstNumber, int secondNumber) {
    return(!(abs(firstNumber - secondNumber) > 1));
}

std::string formatRangeString(int firstNumber, int secondNumber) {
    return (std::to_string(firstNumber) + "-" + std::to_string(secondNumber));
}

std::map<std::string, int> getCurrentIncidentsFromReadings(std::vector<int> chargingCurrentSamples) {
    std::map<std::string, int> output;
    std::string range;
    int firstNumber = 0;
    if(chargingCurrentSamples.size() == 1) {
        range = formatRangeString(chargingCurrentSamples.at(0), chargingCurrentSamples.at(0));
        output[range] = 1;
        return output;
    }
    for(auto number : chargingCurrentSamples) {
        firstNumber = number;
        if()
    }

    return output;
}