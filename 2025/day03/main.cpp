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
    for (const std::string & bank : input)
    {
        int joltage = 0;
        for (int i = 9; i >= 0; i--)
        {
            int it = bank.find_first_of(i + '0');
            if (it != std::string::npos)
            {
                int forward = it + 1;
                int backward = it - 1;
                while (forward < bank.size())
                {
                    if (i * 10 + (bank[forward] - '0') > joltage)
                    {
                        joltage = i * 10 + (bank[forward] - '0');
                    }
                    forward++;
                }

                while (backward >= 0)
                {
                    if ((bank[backward] - '0') * 10 + i > joltage)
                    {
                        joltage = (bank[backward] - '0') * 10 + i;
                    }
                    backward--;
                }
                break;
            }
        }
        result += joltage;
    }

    return result;
}

long long getHighestJoltage(const std::string & bank, int currentDigit = 1, int totalDigits = 12)
{
    for (int i = 9; i >= 0; i--)
    {
        int it = bank.find_first_of(i + '0');
        if (it != std::string::npos && (bank.size() - it - 1) >= (totalDigits - currentDigit))
        {
            if (currentDigit == totalDigits) 
            {
                return i;
            }
            return (i * pow(10, (totalDigits - currentDigit))) + getHighestJoltage(bank.substr(it + 1), currentDigit + 1);
        }
    }
    return 0;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;
    for (const std::string & bank : input)
    {
        result += getHighestJoltage(bank);
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day03_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 357);

    FileHandler fileHandler("input-files/2025/day03.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 3121910778619);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}