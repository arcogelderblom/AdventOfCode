#include <iostream>
#include <chrono>
#include <map>
#include <set>

#include <cassert>

#include "alu.hpp"

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool checkNum(long long num, std::vector<std::string> instructions)
{
    std::map<std::string, int> variablesAndValues;
    variablesAndValues["z"] = 0;
    ALU alu(std::to_string(num));
    
    for (std::string instruction : instructions)
    {
        alu.executeInstruction(instruction, variablesAndValues);
    }
    return variablesAndValues["z"] == 0;
}

long long findValid14DigitNum(std::vector<std::string> instructions, bool largest)
{
    int startNum = 3411111; // educated guess, from 1111111 is also possible but would take a lot longer
    if (largest)
    {
        startNum = 9999999;
    }
    std::vector<int> increment = { 12, 6, 4, 5, 0, -1, -1, 14, -1, 14, -1, -1, -1, -1};
    std::vector<int> required = { 0, 0, 0, 0, 0, 7, 13, 0, 7, 0, 9, 2, 9, 14 };
    std::vector<int> number = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    while (true)
    {
        int startNumIndex = 0;
        long long z = 0;
        for (int i = 0; i < 14; i++)
        {
            int inc = increment[i];
            int req = required[i];

            if (inc != -1)
            {
                z = z * 26 + (std::to_string(startNum)[startNumIndex] - '0') + inc;
                number[i] = (std::to_string(startNum)[startNumIndex] - '0') ;
                startNumIndex++;
            }
            else
            {
                number[i] = (z%26) - req;
                z /= 26;
            }
        }
        
        long long num = 0;
        std::for_each(number.begin(), number.end(), [&](auto& d){num = num * 10 + d;});
        if (z == 0 && std::to_string(num).find('0') == std::string::npos)
        {
            // just to double check, use the *real* implementation of the ALU
            if (checkNum(num, instructions))
            {
                return num;
            }
        }
        
        startNum = largest ? startNum - 1 : startNum + 1;
        while (std::to_string(startNum).find('0') != std::string::npos)// || startNum % 26 != 0)
        {
            startNum = largest ? startNum - 1 : startNum + 1;
        }
    }
}

int main(void)
{
    FileHandler fileHandler("input-files/2021/day24.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 24, puzzle 1: " << std::flush << findValid14DigitNum(input, true) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 24, puzzle 2: " << std::flush << findValid14DigitNum(input, false) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}