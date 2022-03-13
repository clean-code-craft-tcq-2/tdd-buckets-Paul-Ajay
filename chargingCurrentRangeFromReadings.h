#pragma once

#include <iostream>
#include <map>
#include <vector>

bool isValidChargingCurrentSamples(std::vector<int>);
bool isContinuousNumbers(int firstNumber, int secondNumber);
std::string formatRangeString(int firstNumber, int secondNumber);
std::string toCsvFormat(std::map<std::string, int>);
std::string getCurrentIncidentsFromReadings(std::vector<int> chargingCurrentSamples);