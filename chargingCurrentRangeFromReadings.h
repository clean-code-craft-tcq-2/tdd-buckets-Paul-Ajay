#pragma once

#include <iostream>
#include <map>
#include <vector>

bool isContinuousNumbers(int firstNumber, int secondNumber);
std::string formatRangeString(int firstNumber, int secondNumber);
std::map<std::string, int> getCurrentIncidentsFromReadings(std::vector<int> chargingCurrentSamples);