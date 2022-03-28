#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

using functionPtr = void (*)(std::string);

bool isValidChargingCurrentSamples(std::vector<int>);
std::vector<int> doSortVector(std::vector<int>);
bool isContinuousNumbers(int firstNumber, int secondNumber);
std::map<std::string, int> getCurrentRangesAndReadingsMap(std::vector<int>);
std::string formatRangeString(int firstNumber, int secondNumber);
std::string toCsvFormat(std::map<std::string, int>);
void consolePrint(std::string);
int getNumberFromVector(std::vector<int>);
int getCurrentFromADCReading(std::vector<int>, int, int,int);
std::vector<int> convertADCCurrentReadingsToInteger(std::vector<std::vector<int>>, int, int, int);
int getADCMaximumValueFromRange(int);
std::string getCurrentIncidentsFromReadings(std::vector<std::vector<int>>, int, int, int, functionPtr fPtr);
