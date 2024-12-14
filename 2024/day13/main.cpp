#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long getTokensNeededPart1(const long & aAddX, const long & aAddY, const long & bAddX, const long & bAddY, long prizeX, long prizeY)
{
    long aPresses = 0, bPresses = 0;
    long totalPrizeX = prizeX;
    long totalPrizeY = prizeY;
    while (prizeX > 0 && prizeY > 0)
    {
        if ((prizeX % bAddX != 0 || prizeY % bAddY != 0) ||
            (prizeX / bAddX != prizeY / bAddY))
        {
            aPresses++;
            prizeX -= aAddX;
            prizeY -= aAddY;
        }
        else
        {
            bPresses = prizeX / bAddX;
            prizeX -= (bAddX * bPresses);
            prizeY -= (bAddY * bPresses);
        }
    }
        
    if (prizeX == 0 && prizeY == 0)
    {
        return (aPresses * 3) + bPresses;
    }
    return 0;
}

double getTokensNeededPart2(const double & aAddX, const double & aAddY, const double & bAddX, const double & bAddY, const double & prizeX, const double & prizeY)
{
    // they are really two lines, have line A go freely and B directly to prize because of a offset, calculate intersection and derive amount of times you pressed A to get there, then calculate remainder to get b presses
    // line A: y = ay/ax * x
    // line B: y = by/bx * x + offset
    // intersection: ay/ax * x = by/bx * x + offset (x = offset / (ay/ax - by/bx) )
    
    double offset = (prizeY - ((bAddY/bAddX) * prizeX));
    double intersectionX = offset / ((aAddY/aAddX)-(bAddY/bAddX));
    
    double aPresses = intersectionX / aAddX ;
    double bPresses = (prizeX - intersectionX) / bAddX;
    
    if ((std::abs(aPresses - std::round(aPresses)) >= 0.0001f) || (std::abs(bPresses - std::round(bPresses)) >= 0.0001f))
    {
        return 0;
    }
    if (((aAddX * std::round(aPresses)) + (bAddX * std::round(bPresses) == prizeX)) && ((aAddY * std::round(aPresses)) + (bAddY * std::round(bPresses) == prizeY)))
    {
        return (std::round(aPresses) * 3) + std::round(bPresses);
    }
    return 0;
}


long part1(const std::vector<std::string> & input) 
{
    long result = 0;
    for (const std::string & clawMachineStr : input)
    {
        long cost = 0;
        std::vector<std::string> clawMachine = StringParser::toVector(clawMachineStr, "\n");
        long aAddX = std::stoll(clawMachine[0].substr(clawMachine[0].find_first_of('+'), clawMachine[0].find(',') - clawMachine[0].find_first_of('+')));
        long aAddY = std::stoll(clawMachine[0].substr(clawMachine[0].find_last_of('+')));
        long bAddX = std::stoll(clawMachine[1].substr(clawMachine[1].find_first_of('+'), clawMachine[1].find(',') - clawMachine[1].find_first_of('+')));
        long bAddY = std::stoll(clawMachine[1].substr(clawMachine[1].find_last_of('+')));
        long prizeX = std::stoll(clawMachine[2].substr(clawMachine[2].find_first_of('=') + 1, clawMachine[2].find(',') - clawMachine[2].find_first_of('=') + 1));
        long prizeY = std::stoll(clawMachine[2].substr(clawMachine[2].find_last_of('=') + 1));
        
        result += getTokensNeededPart1(aAddX, aAddY, bAddX, bAddY, prizeX, prizeY);
    }
    return result;
}

unsigned long part2(const std::vector<std::string> & input) 
{
    unsigned long result = 0;
    for (const std::string & clawMachineStr : input)
    {
        long cost = 0;
        
        std::vector<std::string> clawMachine = StringParser::toVector(clawMachineStr, "\n");
        long aAddX = std::stoll(clawMachine[0].substr(clawMachine[0].find_first_of('+'), clawMachine[0].find(',') - clawMachine[0].find_first_of('+')));
        long aAddY = std::stoll(clawMachine[0].substr(clawMachine[0].find_last_of('+')));
        long bAddX = std::stoll(clawMachine[1].substr(clawMachine[1].find_first_of('+'), clawMachine[1].find(',') - clawMachine[1].find_first_of('+')));
        long bAddY = std::stoll(clawMachine[1].substr(clawMachine[1].find_last_of('+')));
        long prizeX = std::stoll(clawMachine[2].substr(clawMachine[2].find_first_of('=') + 1, clawMachine[2].find(',') - clawMachine[2].find_first_of('=') + 1));
        long prizeY = std::stoll(clawMachine[2].substr(clawMachine[2].find_last_of('=') + 1));
        
        result += getTokensNeededPart2(aAddX, aAddY, bAddX, bAddY, prizeX + 10000000000000, prizeY + 10000000000000);
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day13_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");

    assert(part1(testinput) == 480);

    FileHandler fileHandler("input-files/2024/day13.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 875318608908);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}