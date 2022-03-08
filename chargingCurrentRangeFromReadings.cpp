#include "chargingCurrentRangeFromReadings.h"

bool isContinuousNumbers(int firstNumber, int secondNumber) {
    return(!(abs(firstNumber - secondNumber) > 1));
}

std::string formatRangeString(int firstNumber, int secondNumber) {
    return (std::to_string(firstNumber) + "-" + std::to_string(secondNumber));
}

std::map<std::string, int> getCurrentIncidentsFromReadings(std::vector<int> chargingCurrentSamples) {
    std::map<std::string, int> output;
    std::string rangeString;
    std::vector<int> continuousRangeReadings;
    for(auto itr = chargingCurrentSamples.begin(); itr != chargingCurrentSamples.end() - 1; itr++) {
        continuousRangeReadings.push_back(*itr);
        if(!isContinuousNumbers(*itr, *(itr + 1))) {
            rangeString = formatRangeString(continuousRangeReadings.front(), continuousRangeReadings.back());
            output[rangeString] = continuousRangeReadings.size();
            continuousRangeReadings.clear();
        }
    }
    continuousRangeReadings.push_back(chargingCurrentSamples.back());
    rangeString = formatRangeString(continuousRangeReadings.front(), continuousRangeReadings.back());
    output[rangeString] = continuousRangeReadings.size();
    return output;
}