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
    std::vector<std::pair<int, int>> directions = { {-1, -1}, {0, -1}, {1, -1},
                                                    {-1, 0},           {1, 0},
                                                    {-1, 1},  {0, 1},  {1, 1}};

    int result = 0;
    for (int x = 0; x < input[0].size(); x++)
    {
        for (int y = 0; y < input.size(); y++)
        {
            if (input[y][x] == '@')
            {
                int adjacentRolls = 0;
                for (const std::pair<int, int> & d : directions)
                {
                    if (x + d.first >= 0 && x + d.first < input[0].size() && y + d.second >= 0 && y + d.second < input.size()) // check bounds
                    {
                        if (input[y + d.second][x + d.first] == '@')
                        {
                            adjacentRolls++;
                        }
                    }
                }
                if (adjacentRolls < 4)
                {
                    result++;
                }
            }
        }
    }
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0; 
    std::vector<std::pair<int, int>> directions = { {-1, -1}, {0, -1}, {1, -1},
                                                    {-1, 0},           {1, 0},
                                                    {-1, 1},  {0, 1},  {1, 1}};
    std::vector<std::pair<int, int>> removedRolls;    
    std::vector<std::string> inputCopy = input;
    bool doneProcessing = false;
    int round = 0;
    while (!doneProcessing)
    {
        for (int x = 0; x < inputCopy[0].size(); x++)
        {
            for (int y = 0; y < inputCopy.size(); y++)
            {
                if (inputCopy[y][x] == '@')
                {
                    int adjacentRolls = 0;
                    for (const std::pair<int, int> & d : directions)
                    {
                        if (x + d.first >= 0 && x + d.first < inputCopy[0].size() && y + d.second >= 0 && y + d.second < inputCopy.size()) // check bounds
                        {
                            if (inputCopy[y + d.second][x + d.first] == '@')
                            {
                                adjacentRolls++;
                            }
                        }
                    }
                    if (adjacentRolls < 4)
                    {
                        removedRolls.push_back({x, y});
                        result++;
                    }
                }
            }
        }
        if (removedRolls.empty()) 
        {
            doneProcessing = true;
        }
        else
        {
            for (const std::pair<int, int> removedRoll : removedRolls)
            {
                inputCopy[removedRoll.second][removedRoll.first] = '.';
            }
            removedRolls.clear();
        }
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day04_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 13);

    FileHandler fileHandler("input-files/2025/day04.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 43);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}