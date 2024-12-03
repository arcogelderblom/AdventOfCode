#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int parsePossibleMulInstruction(const std::string & line, int & i)
{
    const std::string mulInstruction = "mul";
    if (line.substr(i, 3) == mulInstruction)
    {
        if (line[i+3] == '(')
        {
            i += 3;
            int lhs = 0;
            int rhs = 0;
            bool seenComma = false;
            while (line[++i] != ')')
            {
                if (isdigit(line[i]))
                {
                    if (seenComma)
                    {
                        rhs *= 10;
                        rhs += line[i] - '0';
                    }
                    else
                    {
                        lhs *= 10;
                        lhs += line[i] - '0';
                    }
                }
                else if (line[i] == ',' && !seenComma)
                {
                    seenComma = true;
                }
                else
                {
                    return 0;
                }
            }
            
            if (line[i] == ')')
            {
                return lhs*rhs;
            }
        }
    }
    return 0;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    for (const std::string & line : input)
    {
        for (int i = 0; i < line.size(); i++)
        {
            i = line.find_first_of('m', i);
            if (i == std::string::npos)
            {
                break;
            }

            result += parsePossibleMulInstruction(line, i);
        }
    }
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;

    const std::string doInstruction = "do()";
    const std::string dontInstruction = "don't()";

        bool enabled = true;
    for (const std::string & line : input)
    {
        for (int i = 0; i < line.size(); i++)
        {
            i = line.find_first_of("md", i);
            if (i == std::string::npos)
            {
                break;
            }

            if (line[i] == 'd')
            {
                if (line.substr(i, doInstruction.size()) == doInstruction)
                {
                    enabled = true;
                }
                else if (line.substr(i, dontInstruction.size()) == dontInstruction)
                {
                    enabled = false;
                }
                continue;
            }

            if (enabled)
            {
                result += parsePossibleMulInstruction(line, i);
            }
        }
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day03_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 161);

    FileHandler fileHandler("input-files/2024/day03.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    FileHandler testFileHandler2("input-files/2024/day03_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n");
    assert(part2(testinput2) == 48);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}