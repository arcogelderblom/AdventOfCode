#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <set>
#include <algorithm>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

void output(const std::vector<std::string> & vec)
{
    for (const std::string & elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


void output(const std::set<std::string> & s)
{
    for (const std::string & elem : s)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

bool getPossibleTowels(int patternIndex, const std::vector<std::string> & towels, const std::string & pattern, std::set<int> & visitedIndexes)
{
    if (patternIndex == pattern.size())
    {
        return true;
    }
    else if (patternIndex > pattern.size())
    {
        return false;
    }

    visitedIndexes.insert(patternIndex);
    for (const std::string & towel : towels)
    {
        if (pattern.substr(patternIndex, towel.size()) == towel && visitedIndexes.find(patternIndex + towel.size()) == visitedIndexes.end()) 
        {
            if (getPossibleTowels(patternIndex + towel.size(), towels, pattern, visitedIndexes))
            {
                return true;
            }
        }
    }
    return false;
}

unsigned long long getAllPossibleTowels(int patternIndex, const std::vector<std::string> & towels, const std::string & pattern, std::map<int, unsigned long long> & cached)
{
    if (patternIndex == pattern.size())
    {
        return 1;
    }
    else if (patternIndex > pattern.size())
    {
        return 0;
    }
    else if (cached.find(patternIndex) != cached.end())
    {
        return cached[patternIndex];
    }

    for (const std::string & towel : towels)
    {
        if (pattern.substr(patternIndex, towel.size()) == towel)
        {
            cached[patternIndex] += getAllPossibleTowels(patternIndex + towel.size(), towels, pattern, cached);
        }
    }

    return cached[patternIndex];
}



int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<std::string> towels = StringParser::toVector(input[0], ", ");
    std::vector<std::string> patterns = StringParser::toVector(input[1], "\n");

    for (int i = 0; i < patterns.size(); i++)
    {
        std::set<int> visitedIndexes;
        if (getPossibleTowels(0, towels, patterns[i], visitedIndexes))
        {
            result++;
        }
            
    }

    return result;
}

unsigned long long part2(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;
    
    std::vector<std::string> towels = StringParser::toVector(input[0], ", ");
    std::vector<std::string> patterns = StringParser::toVector(input[1], "\n");

    for (int i = 0; i < patterns.size(); i++)
    {
        std::set<int> visitedIndexes;
        if (getPossibleTowels(0, towels, patterns[i], visitedIndexes))
        {
            // it is possible to create this towel with the given patterns, get all options
            std::map<int, unsigned long long> amountOfCombinations;
            result += getAllPossibleTowels(0, towels, patterns[i], amountOfCombinations);
        }
            
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day19_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");
    
    assert(part1(testinput) == 6);

    FileHandler fileHandler("input-files/2024/day19.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 19, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 16);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 19, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}