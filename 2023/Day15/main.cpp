#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <utility>
#include <map>
#include <list>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int runHASH(const std::string & src)
{
    int currentValue = 0;
    for (const char & c : src)
    {
        currentValue += c;
        currentValue *= 17;
        currentValue %= 256;
    }
    // std::cout << src << " : " << currentValue << std::endl;
    return currentValue;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    for (const std::string & str : input)
    {
        result += runHASH(str);
    }
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    std::map<int, std::list<std::pair<int, std::string>>> HASHMAP;
    for (const std::string & str : input)
    {
        if (str.find('-') != std::string::npos)
        {
            std::string label = str.substr(0, str.size() - 1);
            int box = runHASH(label);

            auto it = std::find_if(HASHMAP[box].begin(), HASHMAP[box].end(), [&](const std::pair<int, std::string> & elem){ return elem.second == label; });
            if (it != HASHMAP[box].end())
            {
                HASHMAP[box].erase(it);
            }
        }
        else
        {
            std::string label = str.substr(0, str.find('='));
            int lens = std::stoi(str.substr(str.find('=') + 1));
            int box = runHASH(label);
            auto it = std::find_if(HASHMAP[box].begin(), HASHMAP[box].end(), [&](const std::pair<int, std::string> & elem){ return elem.second == label; });
            if (it != HASHMAP[box].end())
            {
                HASHMAP[box].insert(it, std::make_pair(lens, label));
                HASHMAP[box].erase(it);
            }
            else
            {
                HASHMAP[box].push_back(std::make_pair(lens, label));
            }
        }
    }

    for (const std::pair<int, std::list<std::pair<int, std::string>>> & box : HASHMAP)
    {
        int slot = 1;
        for (const std::pair<int, std::string> & lens : box.second)
        {
            result += (box.first + 1) * slot * lens.first;
            slot++;
        }
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day15_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), ",");
    assert(part1(testInput) == 1320);

    FileHandler fileHandler("input-files/2023/day15.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), ",");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    assert(part2(testInput) == 145);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}