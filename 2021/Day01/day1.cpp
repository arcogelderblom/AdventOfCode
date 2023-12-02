#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int getIncreaseCount(std::vector<int> measurements) 
{
    int increaseCount = 0;
    for (int i = 0; i < measurements.size() - 1; i++) {
        int first = measurements[i];
        int second = measurements[i+1];
        if (second > first) {
            increaseCount++;
        }    
    }
    return increaseCount;
}

int getIncreaseCountSum(std::vector<int> measurements) 
{
    int increaseCount = 0;
    for (int i = 0; i < measurements.size() - 3; i++) {
        int first = measurements[i] + measurements[i+1] + measurements[i+2];
        int second = measurements[i+1] + measurements[i+2] + measurements[i+3];
        if (second > first) {
            increaseCount++;
        }    
    }
    return increaseCount;
}

int main(void) 
{
    std::vector<int> testInput {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
    assert(getIncreaseCount(testInput) == 7);

    FileHandler fileHandler("input-files/2021/day01.txt");
    std::vector<int> measurements = StringParser::toIntVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << getIncreaseCount(measurements) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getIncreaseCountSum(testInput) == 5);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << getIncreaseCountSum(measurements) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}