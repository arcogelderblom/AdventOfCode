#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::vector<std::string> splittedInput = StringParser::toVector(input[0], ",");
    for (const std::string & range : splittedInput)
    {
        std::vector<long long> firstLast = StringParser::toLongLongVector(range, "-");
        for (long long i = firstLast[0]; i <= firstLast[1]; i++)
        {
            std::string s = std::to_string(i);
            if (s.size() % 2 == 0)
            {
                if (s.substr(0, s.size()/2) == s.substr(s.size()/2))
                {
                    result += i;
                }
            }
        }
    }

    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::vector<std::string> splittedInput = StringParser::toVector(input[0], ",");
    for (const std::string & range : splittedInput)
    {
        std::vector<long long> firstLast = StringParser::toLongLongVector(range, "-");
        for (long long i = firstLast[0]; i <= firstLast[1]; i++)
        {
            std::string s = std::to_string(i);
            for (int j = 1; j <= s.size() / 2; j++)
            {
                bool valid = false;
                if (s.size() % j == 0)
                {
                    for (int k = 0; k < (s.size() / j) - 1; k++)
                    {
                        if (s.substr(j * k, j) != s.substr(j * (k + 1), j))
                        {
                            valid = true;
                            break;
                        }
                    }
                }
                else 
                {
                    valid = true;
                }

                if (!valid)
                {
                    result += i;
                    break;
                }
            }
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day02_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 1227775554);

    FileHandler fileHandler("input-files/2025/day02.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 4174379265);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}