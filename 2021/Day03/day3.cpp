#include <iostream>
#include <cassert>
#include <algorithm>
#include <chrono>

#include "FileHandler.hpp"
#include "StringParser.hpp"

char getMostCommonForPosition(std::vector<std::string> diagnosticReport, int positionIndex, char returnWhenEqual) 
{
    int amount1 = 0;
    int amount0 = 0;
    for (std::string item : diagnosticReport)
    {
        if (item[positionIndex] == '1') {
            amount1++;
        }
        else {
            amount0++;
        }
    }
    if (amount1 == amount0) {
        return returnWhenEqual;
    }
    return amount1 > amount0 ? '1' : '0';
}

char getLeastCommonForPosition(std::vector<std::string> diagnosticReport, int positionIndex, char returnWhenEqual) 
{
    int amount1 = 0;
    int amount0 = 0;
    for (std::string item : diagnosticReport)
    {
        if (item[positionIndex] == '1') {
            amount1++;
        }
        else {
            amount0++;
        }
    }
    if (amount1 == amount0) {
        return returnWhenEqual;
    }
    return amount1 < amount0 ? '1' : '0';
}

std::string getGammaRateAsBinaryString(std::vector<std::string> diagnosticReport) 
{
    std::string gammaRateBinary;
    for (int i = 0; i < diagnosticReport[0].size(); i++)
    {
        gammaRateBinary += getMostCommonForPosition(diagnosticReport, i, '0');
    }
    return gammaRateBinary;
}

std::string getEpsilonRateAsBinaryStringFromGammaRate(std::string gammaRateAsBinaryString) 
{
    std::string episilonRateBinary;
    for (int i = 0; i < gammaRateAsBinaryString.size(); i++)
    {
        if (gammaRateAsBinaryString[i] == '1') 
        {
            episilonRateBinary += '0';
        }
        else
        {
            episilonRateBinary += '1';
        }
    }
    return episilonRateBinary;
}

int getPowerConsumption(std::vector<std::string> diagnosticReport)
{
    std::string gammaRateBinary = getGammaRateAsBinaryString(diagnosticReport);
    std::string episilonRateBinary = getEpsilonRateAsBinaryStringFromGammaRate(gammaRateBinary);
    int gammaRate = std::stoi(gammaRateBinary, 0, 2);
    int epsilonRate = std::stoi(episilonRateBinary, 0, 2);
    return gammaRate * epsilonRate;
}

int getOxygenGeneratorRating(std::vector<std::string> diagnosticReport)
{
    int i = 0;
    while (diagnosticReport.size() > 1)
    {
        char mostCommon = getMostCommonForPosition(diagnosticReport, i, '1');    
        diagnosticReport.erase(std::remove_if(
            diagnosticReport.begin(), diagnosticReport.end(),
            [&](const std::string& item) { 
                return item[i] != mostCommon;
            }), diagnosticReport.end());
        i++;
    }
    // only 1 number left
    return stoi(diagnosticReport[0], 0, 2);
}

int getCO2ScrubberRating(std::vector<std::string> diagnosticReport)
{
    int i = 0;
    while (diagnosticReport.size() > 1)
    {
        char leastCommon = getLeastCommonForPosition(diagnosticReport, i, '0');
        diagnosticReport.erase(std::remove_if(
            diagnosticReport.begin(), diagnosticReport.end(),
            [&](const std::string& item) { 
                return item[i] != leastCommon;
            }), diagnosticReport.end());
        i++;
    }
    // only 1 number left
    return stoi(diagnosticReport[0], 0, 2);
}

int getLifeSupplyRating(std::vector<std::string> diagnosticReport)
{
    return getOxygenGeneratorRating(diagnosticReport) * getCO2ScrubberRating(diagnosticReport);
}

int main(void)
{
    std::vector<std::string> testData = {"00100", "11110", "10110", "10111", "10101", "01111", "00111", "11100", "10000", "11001", "00010", "01010"};
    assert(getPowerConsumption(testData) == 198);

    FileHandler fileHandler("input-files/2021/day03.txt");
    std::vector<std::string> diagnosticReport = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 1: " << std::flush << getPowerConsumption(diagnosticReport) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getLifeSupplyRating(testData) == 230);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 2: " << std::flush << getLifeSupplyRating(diagnosticReport) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}