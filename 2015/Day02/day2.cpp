#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <numeric>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int getSquareFeetWrappingPaper(std::string dimensions)
{
    std::vector<std::string> separatedDimensions = StringParser::toVector(dimensions, "x");
    // 2*l*w + 2*w*h + 2*h*l
    int l = std::stoi(separatedDimensions[0]);
    int w = std::stoi(separatedDimensions[1]);
    int h = std::stoi(separatedDimensions[2]);
    std::vector<int> dimensionsInt = { l*w, w*h, h*l };
    std::sort(dimensionsInt.begin(), dimensionsInt.end());
    int sum = 0;
    std::for_each(dimensionsInt.begin(), dimensionsInt.end(), [&](const int i) { sum += i * 2; });
    return sum + dimensionsInt[0];
}

int getSquareFeetWrappingPaper(std::vector<std::string> inputDimensions)
{
    int sum = 0;
    for (const std::string & dimensions : inputDimensions)
    {
        sum += getSquareFeetWrappingPaper(dimensions);
    }
    return sum;
}

int getFeetOfRibbon(std::string dimensions)
{
    std::vector<std::string> separatedDimensions = StringParser::toVector(dimensions, "x");
    // 2*l*w + 2*w*h + 2*h*l
    int l = std::stoi(separatedDimensions[0]);
    int w = std::stoi(separatedDimensions[1]);
    int h = std::stoi(separatedDimensions[2]);
    std::vector<int> dimensionsInt = { l, w, h };
    std::sort(dimensionsInt.begin(), dimensionsInt.end());
    int ribbon = (dimensionsInt[0] * 2) + (dimensionsInt[1] * 2);
    int bow = l*w*h;
    return ribbon + bow;
}

int getFeetOfRibbon(std::vector<std::string> inputDimensions)
{
    int sum = 0;
    for (const std::string & dimensions : inputDimensions)
    {
        sum += getFeetOfRibbon(dimensions);
    }
    return sum;
}

int main(void) 
{
    assert(getSquareFeetWrappingPaper("2x3x4") == 58);
    assert(getSquareFeetWrappingPaper("1x1x10") == 43);
    FileHandler FileHandler("input-files/2015/day02.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 1: " << std::flush << getSquareFeetWrappingPaper(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 2: " << std::flush << getFeetOfRibbon(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}