#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

unsigned long long calculate(const std::vector<int> & nums, const std::string & operators)
{
    unsigned long long result = nums[0];
    for (int i = 0; i < operators.size(); i++)
    {
        if (operators[i] == '+')
        {   
            result += nums[i+1];
        }
        else if (operators[i] == '*')
        {
            result *= nums[i+1]; 
        }
        else if (operators[i] == '|')
        {
            std::string tmp = std::to_string(result) + std::to_string(nums[i+1]);
            result = std::stoull(tmp);
        }
    }

    return result;
}

static std::map<int, std::vector<std::string>> optionsPart1;

std::vector<std::string> getAllOperatorOptionsPart1(int amountOfOperators)
{  
    if (optionsPart1.find(amountOfOperators) != optionsPart1.end())
    {
        return optionsPart1[amountOfOperators];
    }

    std::vector<std::string> allOptions;
    for (int amountMultiply = 0; amountMultiply <= amountOfOperators; amountMultiply++)
    {
        std::string multiply(amountMultiply, '*');
        for (int amountAdd = amountOfOperators - amountMultiply; amountAdd <= amountOfOperators - amountMultiply; amountAdd++)
        {
            std::string add(amountAdd, '+');
            std::string current = multiply + add;
            do
            {
                allOptions.push_back(current);
            }
            while (std::next_permutation(current.begin(), current.end()));
        }
    }

    optionsPart1[amountOfOperators] = allOptions;
    return allOptions;
}

static std::map<int, std::vector<std::string>> optionsPart2;

std::vector<std::string> getAllOperatorOptionsPart2(int amountOfOperators)
{  
    if (optionsPart2.find(amountOfOperators) != optionsPart2.end())
    {
        return optionsPart2[amountOfOperators];
    }

    std::vector<std::string> allOptions;
    for (int amountMultiply = 0; amountMultiply <= amountOfOperators; amountMultiply++)
    {
        std::string multiply(amountMultiply, '*');
        for (int amountAdd = 0; amountAdd <= amountOfOperators - amountMultiply; amountAdd++)
        {
            std::string add(amountAdd, '+');
            for (int amountConcatenation = amountOfOperators - amountMultiply - amountAdd; amountConcatenation <= amountOfOperators - amountMultiply - amountAdd; amountConcatenation++)
            {
                std::string concat(amountConcatenation, '|');
                std::string current = multiply + add + concat;
                do
                {
                    allOptions.push_back(current);
                }
                while (std::next_permutation(current.begin(), current.end()));
            }
        }
    }
    
    optionsPart2[amountOfOperators] = allOptions;
    return allOptions;
}

unsigned long long part1(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;
    for (const std::string & line : input)
    {
        unsigned long long equationResult = std::stoull(line.substr(0, line.find(':')));
        std::vector<int> nums = StringParser::toIntVector(line.substr(line.find(": ") + 2), " ");
        std::vector<std::string> operatorsOptions = getAllOperatorOptionsPart1(nums.size() - 1);
        for (const std::string & operators : operatorsOptions)
        {   
            if (calculate(nums, operators) == equationResult)
            {
                result += equationResult;
                // if 1 operators combination is already right it counts, so no need to check all
                break;
            }
        }
    }

    return result;
}

unsigned long long part2(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;
    
    for (const std::string & line : input)
    {
        unsigned long long equationResult = std::stoull(line.substr(0, line.find(':')));
        std::vector<int> nums = StringParser::toIntVector(line.substr(line.find(": ") + 2), " ");
        std::vector<std::string> operatorsOptions = getAllOperatorOptionsPart1(nums.size() - 1);

        bool solvedInPart1 = false;
        for (const std::string & operators : operatorsOptions)
        {   
            if (calculate(nums, operators) == equationResult)
            {
                solvedInPart1 = true;
                result += equationResult;
                // if 1 operators combination is already right it counts, so no need to check all
                break;
            }
        }

        // if not solved in part 1, generate options for part 2 and try with that
        if (!solvedInPart1)
        {
            operatorsOptions = getAllOperatorOptionsPart2(nums.size() - 1);
            for (const std::string & operators : operatorsOptions)
            {   
                if (calculate(nums, operators) == equationResult)
                {
                    result += equationResult;
                    // if 1 operators combination is already right it counts, so no need to check all
                    break;
                }
            }
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day07_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 3749);

    FileHandler fileHandler("input-files/2024/day07.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 11387);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}