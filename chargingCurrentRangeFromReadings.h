#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

bool isValidChargingCurrentSamples(std::vector<int>);
std::vector<int> doSortVector(std::vector<int>);
bool isContinuousNumbers(int firstNumber, int secondNumber);
std::map<std::string, int> getCurrentRangesAndReadingsMap(std::vector<int>);
std::string formatRangeString(int firstNumber, int secondNumber);
std::string toCsvFormat(std::map<std::string, int>);
std::string getCurrentIncidentsFromReadings(std::vector<int> chargingCurrentSamples);