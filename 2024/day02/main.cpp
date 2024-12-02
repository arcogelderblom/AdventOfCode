#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

// returns false when levels aren't from a safereport
bool checkLevels(const std::vector<int> & levels)
{
    bool increasing = (levels[0] - levels[1]) > 0; // if false then it is decreasing
    for (int i = 0; i < levels.size()-1; i++)
    {
        int difference = levels[i] - levels[i+1];
        
        if (increasing && (difference < 0))
        {
            return false;
        }
        if (!increasing && (difference > 0))
        {
            return false;
        }

        if (std::abs(difference) > 3 || std::abs(difference) < 1)
        {
            return false;
        }
    }

    return true;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    for (const std::string & report : input)
    {
        std::vector<int> levels = StringParser::toIntVector(report, " ");
        if (checkLevels(levels))
        {
            result++;
        }
    }
    
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;

    for (const std::string & report : input)
    {
        std::vector<int> levels = StringParser::toIntVector(report, " ");
        if (checkLevels(levels))
        {
            result++;
        }
        else
        {
            for (int indexToSkip = 0; indexToSkip <= levels.size() - 1; indexToSkip++)
            {
                std::vector<int> alteredLevels = levels;
                alteredLevels.erase(alteredLevels.begin() + indexToSkip);

                if (checkLevels(alteredLevels))
                {
                    result++;
                    break;
                }
            }
        }


    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day02_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 2);

    FileHandler fileHandler("input-files/2024/day02.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 4);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}