#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    int currentSetting = 50;
        
    for (const std::string & instruction : input)
    {
        if (instruction[0] == 'L')
        {
            currentSetting -= std::stoi(instruction.substr(1)) % 100;
            if (currentSetting < 0)
            {
                currentSetting = 99 - std::abs(currentSetting) + 1;
            }
        }
        else
        {
            currentSetting += std::stoi(instruction.substr(1)) % 100;   
            if (currentSetting > 99)
            {
                currentSetting -= 99 + 1;
            }
        }

        if (currentSetting == 0) 
        {
            result++;
        }
    }
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    int result2 = 0;
    int currentSetting = 50;
    int currentSetting2 = 50;
    int i = 0;

    // brute force
    for (const std::string & instruction : input)
    {
        if (instruction[0] == 'L')
        {
            for (int i = 0; i < std::stoi(instruction.substr(1)); i++)
            {
                currentSetting--;
                if (currentSetting == 0)
                {
                    result++;
                }
                else if (currentSetting == -1)
                {
                    currentSetting = 99;
                }
            }
        }
        else
        {
            for (int i = 0; i < std::stoi(instruction.substr(1)); i++)
            {
                currentSetting++;
                if (currentSetting == 100)
                {
                    currentSetting = 0;
                    result++;
                }
            }
        }
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day01_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 3);

    FileHandler fileHandler("input-files/2025/day01.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 6);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}