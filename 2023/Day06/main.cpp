#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <algorithm>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long getAmountOfOptions(long timeMax, long distanceMax)
{
    long min = 0;
    long max = 0;
    for (long time = 1; time <= timeMax; time++)
    {
        long distance = (timeMax - time)*time;
        if (distance > distanceMax)
        {
            min = time;
        }
    }
    for (long time = timeMax; time >= 1; time--)
    {
        long distance = (timeMax - time)*time;
        if (distance > distanceMax)
        {
            max = time;
        }
    }
    
    return min - max + 1;
}

long part1(const std::vector<std::string> & input) 
{
    std::string num = "1234567890";
    int iTimes = 0, iDistances = 0;
    std::string curTimeStr, curDistanceStr;
    std::map<int, int> holdTimeAndDistance = {{0,0}};
    std::vector<long> allOptions;
    while(iTimes <= input[0].size())
    {
        if (std::isdigit(input[0][iTimes]))
        {
            curTimeStr += input[0][iTimes];
        }
        if (std::isdigit(input[1][iDistances]))
        {
            curDistanceStr += input[1][iDistances];
        }
        if (iTimes == input[0].size() || (input[0][iTimes+1] == ' ' && input[1][iDistances+1] == ' '))
        {
            if (!curTimeStr.empty() && !curDistanceStr.empty())
            {
                allOptions.push_back(getAmountOfOptions(std::stol(curTimeStr), std::stol(curDistanceStr)));
                curTimeStr = "";
                curDistanceStr = "";
            }
        }
        iTimes++;
        iDistances++;
    }
    
    long result = 1;
    for (const int & options : allOptions)
    {
        result *= options;
    }
    return result;
}

long part2(const std::vector<std::string> & input) 
{
    long result = 0;
    std::string num = "1234567890";
    int iTimes = 0, iDistances = 0;
    std::string curTimeStr, curDistanceStr;
    std::map<int, int> holdTimeAndDistance = {{0,0}};
    std::vector<int> allOptions;
    while(iTimes <= input[0].size())
    {
        if (std::isdigit(input[0][iTimes]))
        {
            curTimeStr += input[0][iTimes];
        }
        if (std::isdigit(input[1][iDistances]))
        {
            curDistanceStr += input[1][iDistances];
        }
        iTimes++;
        iDistances++;
    }
    
    result = getAmountOfOptions(std::stol(curTimeStr), std::stol(curDistanceStr));
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day06_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 288);

    FileHandler fileHandler("input-files/2023/day06.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 71503);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}