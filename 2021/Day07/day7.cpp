#include <iostream>
#include <cassert>
#include <map>
#include <algorithm>
#include <chrono>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int getLeastFuelCommonPosition(std::vector<int> initialStatePositions, bool incrementingFuelCount)
{
    int minElement = *std::min_element(initialStatePositions.begin(), initialStatePositions.end());
    int maxElement = *std::max_element(initialStatePositions.begin(), initialStatePositions.end());

    std::map<int, int> fuelAndCommonPosition;

    for (int position = minElement; position <= maxElement; position++)
    {
        int totalFuel = 0;
        for (int currentPosition : initialStatePositions)
        {
            if (incrementingFuelCount)
            {
                totalFuel += (std::abs(currentPosition - position) * (std::abs(currentPosition - position) + 1)) / 2;
            }
            else
            {
                totalFuel += std::abs(currentPosition - position);
            }
        }
        fuelAndCommonPosition[totalFuel] = position;
    }

    return fuelAndCommonPosition.begin()->first;
}

int main(void)
{
    std::vector<int> initialStatePositionsTest = StringParser::toIntVector("16,1,2,0,4,2,7,1,2,14", ",");
    assert(getLeastFuelCommonPosition(initialStatePositionsTest, false) == 37);

    FileHandler fileHandler("input-files/2021/day07.txt");
    std::vector<int> initialStatePositions = StringParser::toIntVector(fileHandler.getBuffer(), ",");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 1: " << std::flush << getLeastFuelCommonPosition(initialStatePositions, false) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getLeastFuelCommonPosition(initialStatePositionsTest, true) == 168);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 2: " << std::flush << getLeastFuelCommonPosition(initialStatePositions, true) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
