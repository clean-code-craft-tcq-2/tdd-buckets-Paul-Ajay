#include "chargingCurrentRangeFromReadings.h"

bool isValidChargingCurrentSamples(std::vector<int> chargingCurrentSamples) {
    for(auto itr : chargingCurrentSamples) {
        if(itr < 0)
            return false;
    }
    return true;
}

std::vector<int> doSortVector(std::vector<int> chargingCurrentSamples) {
    std::vector<int> sortedVector = chargingCurrentSamples;
    std::sort(sortedVector.begin(), sortedVector.end());
    return sortedVector;
}

bool isContinuousNumbers(int firstNumber, int secondNumber) {
    return(!(abs(firstNumber - secondNumber) > 1));
}

std::string formatRangeString(int firstNumber, int secondNumber) {
    return (std::to_string(firstNumber) + "-" + std::to_string(secondNumber));
}

std::string toCsvFormat(std::map<std::string, int> continuousRangeReadingsMap) {
    std::string outputString = "Range, Readings";
    for (auto itr : continuousRangeReadingsMap) {
        outputString += "\n" + itr.first + ", " + std::to_string(itr.second);
    }
    return outputString;
}

std::string getCurrentIncidentsFromReadings(std::vector<int> chargingCurrentSamples) {
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
    return toCsvFormat(output);
}