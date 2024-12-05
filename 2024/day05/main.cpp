#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::map<int, std::set<int>> getPageOrderingRules(const std::string & str)
{
    std::map<int, std::set<int>> rules;
    std::vector<std::string> lines = StringParser::toVector(str, "\n");
    for (const std::string & line : lines)
    {
        int pageNum = std::stoi(line.substr(0, line.find('|')));
        int comesBefore = std::stoi(line.substr(line.find('|') + 1));
        rules[pageNum].insert(comesBefore);
    }

    return rules;
}

bool isValidUpdate(const std::vector<int> & update, std::map<int, std::set<int>> & pageOrderingRules)
{
    for (int i = 0; i < update.size() - 1; i++)
    {
        for (int j = i + 1; j < update.size(); j++)
        {
            if (pageOrderingRules[update[i]].find(update[j]) == pageOrderingRules[update[i]].end())
            {
                return false;
            }
        }
    }
    return true;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::map<int, std::set<int>> pageOrderingRules = getPageOrderingRules(input[0]);
    std::vector<std::string> updates = StringParser::toVector(input[1], "\n");
    for (const std::string & updateStr : updates)
    {
        std::vector<int> update = StringParser::toIntVector(updateStr, ",");
        if (isValidUpdate(update, pageOrderingRules))
        {
            result += update[(update.size() - 1 )/ 2];
        }
    }

    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;

    std::map<int, std::set<int>> pageOrderingRules = getPageOrderingRules(input[0]);
    std::vector<std::string> updates = StringParser::toVector(input[1], "\n");
    for (const std::string & updateStr : updates)
    {
        std::vector<int> update = StringParser::toIntVector(updateStr, ",");
        if (!isValidUpdate(update, pageOrderingRules))
        { 
            do
            {
                for (int i = 0; i < update.size() - 1; i++)
                {
                    for (int j = i + 1; j < update.size(); j++)
                    {
                        if (pageOrderingRules[update[i]].find(update[j]) == pageOrderingRules[update[i]].end())
                        {
                            std::iter_swap(update.begin() + i, update.begin() + j);
                            i = -1;
                            break;
                        }
                    }
                }
            } while (!isValidUpdate(update, pageOrderingRules));
            
            result += update[(update.size() - 1 )/ 2];
        }
    }

    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day05_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");
    assert(part1(testinput) == 143);

    FileHandler fileHandler("input-files/2024/day05.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 123);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}