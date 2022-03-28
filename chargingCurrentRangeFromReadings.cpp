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
    return(abs(firstNumber - secondNumber) <= 1);
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

std::map<std::string, int> getCurrentRangesAndReadingsMap(std::vector<int> chargingCurrentSamples) {
    std::map<std::string, int> currentReadingsMap;
    std::string rangeString;
    std::vector<int> continuousRangeReadings;
    for(auto itr = chargingCurrentSamples.begin(); itr != chargingCurrentSamples.end() - 1; itr++) {
        continuousRangeReadings.push_back(*itr);
        if(!isContinuousNumbers(*itr, *(itr + 1))) {
            rangeString = formatRangeString(continuousRangeReadings.front(), continuousRangeReadings.back());
            currentReadingsMap[rangeString] = continuousRangeReadings.size();
            continuousRangeReadings.clear();
        }
    }
    continuousRangeReadings.push_back(chargingCurrentSamples.back());
    rangeString = formatRangeString(continuousRangeReadings.front(), continuousRangeReadings.back());
    currentReadingsMap[rangeString] = continuousRangeReadings.size();
    return currentReadingsMap;
}

void consolePrint(std::string outputString) {
    std::cout<<outputString;
}

int getNumberFromVector(std::vector<int>inputVector) {
    int output = 0;
    for (auto i : inputVector)
        output = output * 10 + i;
    return output;
}

int getCurrentFromADCReading(std::vector<int> adcValue, int adcMaximumValue, int maximumCurrentValue, int minimumCurrentValue) {
    auto adcValueAsSingleNumber = getNumberFromVector(adcValue);
    if((adcValueAsSingleNumber > adcMaximumValue) || (adcValueAsSingleNumber < 0)) {
        return minimumCurrentValue - 1; // Error
    } else {
        double currentValueInAmp = minimumCurrentValue + static_cast<double>((maximumCurrentValue - minimumCurrentValue) * adcValueAsSingleNumber) / adcMaximumValue;
        return round(currentValueInAmp);
    }
}

std::vector<int> convertADCCurrentReadingsToInteger(std::vector<std::vector<int>> currentReadingsAsADC, int adcMaximumValue, int maximumCurrentValue, int minimumCurrentValue) {
    std::vector<int> currentReadingsAsInteger;
    for (auto itr : currentReadingsAsADC) {
        auto currentReadingAsInteger = getCurrentFromADCReading(itr, adcMaximumValue, maximumCurrentValue, minimumCurrentValue);
        if (currentReadingAsInteger < minimumCurrentValue) {
            currentReadingsAsInteger.push_back(-1);
        } else {
            currentReadingsAsInteger.push_back(abs(currentReadingAsInteger));
        }
    }
    return currentReadingsAsInteger;
}

int getADCMaximumValueFromRange(int adcRange) {
    return (pow(2, adcRange) - 2);
}

std::string getCurrentIncidentsFromReadings(std::vector<std::vector<int>> currentReadingsAsADC, int adcRange, int maximumCurrentValue, int minimumCurrentValue, functionPtr fPtr) {
    auto adcMaximumValue = getADCMaximumValueFromRange(adcRange);
    auto chargingCurrentSamples = convertADCCurrentReadingsToInteger(currentReadingsAsADC, adcMaximumValue, maximumCurrentValue, minimumCurrentValue);
    if (!isValidChargingCurrentSamples(chargingCurrentSamples))
        return "";
    auto sortedChargingCurrentSamples = doSortVector(chargingCurrentSamples);
    auto currentReadingsMap = getCurrentRangesAndReadingsMap(sortedChargingCurrentSamples);
    auto csvConvertedString = toCsvFormat(currentReadingsMap);
    (*fPtr)(csvConvertedString);
    return csvConvertedString;
}