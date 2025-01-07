#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>
#include <algorithm>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::string getInstructions(const std::string & sequence, std::map<char, std::pair<int, int>> & keypad)
{
    std::pair<int, int> current = keypad['A'];
    std::string instructions;
    for (const char & c : sequence)
    {
        std::pair<int, int> start = current;
        if (start == keypad[c])
        {
            instructions += 'A';
            continue;
        }

        std::string nextInstruction;
        while (current != keypad[c])
        {
            if (keypad[c].first - current.first < 0)
            {
                std::pair<int, int> next = { keypad[c].first , current.second };
                if (next != keypad['.'])
                {
                    nextInstruction.append(std::abs(keypad[c].first - current.first), '<');
                    current = next;
                }
            }
            if (keypad[c].second - current.second > 0)
            {
                std::pair<int, int> next = { current.first, keypad[c].second };
                if (next != keypad['.'])
                {
                    nextInstruction.append(keypad[c].second - current.second, 'v');
                    current = next;
                }
            }
            if (keypad[c].second - current.second < 0)
            {
                std::pair<int, int> next = { current.first, keypad[c].second };
                if (next != keypad['.'])
                {
                    nextInstruction.append(std::abs(keypad[c].second - current.second), '^');
                    current = next;
                }
            }
            if (keypad[c].first - current.first > 0)
            {
                std::pair<int, int> next = { keypad[c].first , current.second };
                if (next != keypad['.'])
                {
                    nextInstruction.append(keypad[c].first - current.first, '>');
                    current = next;
                }
            }
        }
        instructions += nextInstruction + 'A';
    }

    return instructions;
}

std::map<char, std::pair<int, int>> getNumbersKeypad()
{
    
    // 789
    // 456
    // 123
    // .0A
    std::map<char, std::pair<int, int>> keypad = { { '7', { 0, 0 } },
                                                   { '8', { 1, 0 } },
                                                   { '9', { 2, 0 } },
                                                   { '4', { 0, 1 } },
                                                   { '5', { 1, 1 } },
                                                   { '6', { 2, 1 } },
                                                   { '1', { 0, 2 } },
                                                   { '2', { 1, 2 } },
                                                   { '3', { 2, 2 } },
                                                   { '.', { 0, 3 } },
                                                   { '0', { 1, 3 } },
                                                   { 'A', { 2, 3 } } };
    return keypad;
}

std::map<char, std::pair<int, int>> getArrowsKeypad()
{
    // .^A
    // <v>
    std::map<char, std::pair<int, int>> arrows = { { '.', { 0, 0 } },
                                                   { '^', { 1, 0 } },
                                                   { 'A', { 2, 0 } },
                                                   { '<', { 0, 1 } },
                                                   { 'v', { 1, 1 } },
                                                   { '>', { 2, 1 } } };
    return arrows;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;

    std::map<char, std::pair<int, int>> keypad = getNumbersKeypad();
    std::map<char, std::pair<int, int>> arrows = getArrowsKeypad();
                                    
    for (const std::string & code : input)
    {
        std::string firstRobot = getInstructions(code, keypad);
        std::string secondRobot = getInstructions(firstRobot, arrows);
        std::string thirdRobot = getInstructions(secondRobot, arrows);
        result += (thirdRobot.size() * std::stoi(code.substr(0, 3)));
    }

    return result;
}

unsigned long long part2(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;
    
    std::map<char, std::pair<int, int>> keypad = getNumbersKeypad();
    std::map<char, std::pair<int, int>> arrows = getArrowsKeypad();

    for (const std::string & code : input)
    {
        std::string firstRobot = getInstructions(code, keypad);
        std::map<std::string, long long> cache = { { firstRobot, 1 } };
        for (int i = 0; i < 25; i++)
        {
            std::map<std::string, long long> newCache;
            for (const std::pair<std::string, long long> & elem : cache)
            {
                std::string _;
                for (int j = 0; j < elem.first.size(); j++)
                { 
                    _ += elem.first[j];
                    if (elem.first[j] == 'A')
                    {
                        newCache[_] += elem.second;
                        _.clear();
                    }
                }
            }
            
            cache.clear();
            for (const std::pair<std::string, long long> & elem : newCache)
            {
                std::string _;
                for (int j = 0; j < elem.first.size(); j++)
                { 
                    _ += elem.first[j];
                    if (elem.first[j] == 'A')
                    {
                        cache[getInstructions(_, arrows)] += elem.second;
                        _.clear();
                    }
                }
            }
        }

        long long total = 0;
        for (const std::pair<std::string, long long> & elem : cache)
        {
            total += elem.first.size() * elem.second;
        }

        result += total * std::stoi(code.substr(0, 3));
    }

    return result;
}

int main(void)
{
    FileHandler testFileHandler("input-files/2024/day21_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    
    assert(part1(testinput) == 126384);

    FileHandler fileHandler("input-files/2024/day21.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 21, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 154115708116294);
    
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 21, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}