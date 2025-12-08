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
    
    for (int i = 0; i < input[input.size() - 1].size(); i++)
    {
        char op = input[input.size() - 1][i];
        int slice = input[input.size() - 1].find_first_of("*+", i + 1) - i - 1;
        long long answer = (op == '*' ? 1 : 0);
        for (int j = 0; j < input.size() - 1; j++)
        {
            if (op == '*')
            {
                answer *= std::stoi(input[j].substr(i, slice));
            }
            else
            {
                answer += std::stoi(input[j].substr(i, slice));   
            }
        }
        i += slice;
        result += answer;
    }
    
    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0; 
    
    for (int i = 0; i < input[input.size() - 1].size(); i++)
    {
        char op = input[input.size() - 1][i];
        int slice = 0;
        auto it = input[input.size() - 1].find_first_of("*+", i + 1);
        if (it != std::string::npos)
        {
            slice = it - i - 1;
        }
        else 
        {
            slice = input[input.size() - 1].size() - i;
        }

        long long answer = (op == '*' ? 1 : 0);
        for (int k = i + slice - 1; k >= i; k--)
        {
            std::string num;
            for (int j = 0; j < input.size() - 1; j++)
            {
                num += input[j][k];
            }
            if (op == '*')
            {
                answer *= std::stoi(num);
            }
            else
            {
                answer += std::stoi(num);   
            }
        }
        i += slice;
        result += answer;
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day06_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 4277556);

    FileHandler fileHandler("input-files/2025/day06.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 3263827);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}