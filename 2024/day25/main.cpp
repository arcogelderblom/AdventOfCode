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

    std::vector<std::vector<int>> locks, keys;

    for (const std::string & line : input)
    {
        std::vector<std::string> schematic = StringParser::toVector(line, "\n");
        // determine whether it is a key or a lock
        bool isLock = (schematic[0] == std::string(schematic[0].size(), '#'));
        if (isLock)
        {
            std::vector<int> lock;
            for (int i = 0; i < schematic[0].size(); i++)
            {
                for (int height = 0; height < schematic.size(); height++)
                {
                    if (schematic[height][i] == '.')
                    {
                        lock.push_back(height-1);
                        break;
                    }
                } 
            }
            locks.push_back(lock);
        }
        else
        {
            std::vector<int> key;
            for (int i = 0; i < schematic[0].size(); i++)
            {
                for (int height = 0; height < schematic.size(); height++)
                {
                    if (schematic[height][i] == '#')
                    {
                        key.push_back((schematic.size() - 1) - height);
                        break;
                    }
                } 
            }
            keys.push_back(key);
        }
    }

    for (const std::vector<int> & lock : locks)
    {
        for (const std::vector<int> & key : keys)
        {
            bool fits = true;
            for (int i = 0; i < lock.size(); i++)
            {
                if (lock[i] + key[i] > 5)
                {
                    fits = false;
                    break;
                }
            }

            if (fits)
            {
                result++;
            }
        }
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day25_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");

    assert(part1(testinput) == 3);

    FileHandler fileHandler("input-files/2024/day25.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 25, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}