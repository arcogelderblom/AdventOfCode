#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

void blink(std::map<std::string, long long> & stones)
{
    std::map<std::string, long long> newStones;
    for (const std::pair<std::string, long long> & stone : stones)
    {
        if (stone.first == "0")
        {
            newStones["1"] += stone.second;
        }
        else if (stone.first.size() % 2 == 0)
        {
            newStones[std::to_string(std::stoll(stone.first.substr(0, stone.first.size() / 2)))] += stone.second;
            newStones[std::to_string(std::stoll(stone.first.substr(stone.first.size() / 2)))] += stone.second;
        }
        else
        {
            newStones[std::to_string(std::stoll(stone.first) * 2024)] += stone.second;
        }

    }
    stones = newStones;
}

void blinkTimes(std::map<std::string, long long> & stones, int times)
{
    for (int i = 0; i < times; i++)
    {
        blink(stones);
    }
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::vector<std::string> stonesVec = StringParser::toVector(input[0], " ");
    std::map<std::string, long long> stones;
    
    for (const std::string & stone : stonesVec)
    {
        stones[stone]++;
    }

    blinkTimes(stones, 25);

    for (const auto & stoneAndAmount : stones)
    {
        result += stoneAndAmount.second;
    }
    
    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::vector<std::string> stonesVec = StringParser::toVector(input[0], " ");
    std::map<std::string, long long> stones;
    
    for (const std::string & stone : stonesVec)
    {
        stones[stone]++;
    }

    blinkTimes(stones, 75);

    for (const auto & stoneAndAmount : stones)
    {
        result += stoneAndAmount.second;
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day11_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 55312);
    
    FileHandler fileHandler("input-files/2024/day11.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}