#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include <map>

int part1(const std::vector<std::string> & input)
{
    int result = 0;
    std::map<int, int> presentAndSize;
    for (int i = 0; i < input.size() - 1; i++)
    {
        int area = 0;
        for (const std::string & slice : StringParser::toVector(input[i], "\n"))
        {
            area += std::count(slice.begin(), slice.end(), '#');
        }
        presentAndSize[i] = area;
    }

    for (const std::string & region : StringParser::toVector(input[input.size() - 1], "\n"))
    {
        int size = std::stoi(region.substr(0, region.find('x'))) * std::stoi(region.substr(region.find('x') + 1, region.find(':') - region.find('x') - 1));
        int totalPresentsSize = 0;
        std::vector<int> amounts = StringParser::toIntVector(region.substr(region.find(' ') + 1), " ");
        for (int i = 0; i < input.size() - 1; i++)
        {
            totalPresentsSize += amounts[i] * presentAndSize[i];
        }

        // if the total area of the presents fit, then count them
        if (totalPresentsSize < size)
        {
            result++;
        }
    }

    return result;
}

int main(void) 
{
    FileHandler fileHandler("input-files/2025/day12.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}