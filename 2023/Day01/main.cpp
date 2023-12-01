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
    for (const std::string & line : input)
    {
        int current = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (isdigit(line[i]))
            {
                current += (line[i] - '0') * 10;
                break;
            }
        }
        for (int i = line.size() - 1; i >= 0; i--)
        {
            if (isdigit(line[i]))
            {
                current += line[i] - '0';
                break;
            }
        }
        
        result += current;
    }
    
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    for (const std::string & line : input)
    {
        int current = 0;
        for (int i = 0; i < line.size(); i++)
        {
            std::string firstChars = "otfsen";
            auto it = firstChars.find(line[i]); // check if current char is first char of a written number
            if (it != std::string::npos)
            {
                try {
                    switch (it)
                    {
                        case 0:
                            if (line.substr(i, 3) == "one")
                            {
                                current += 1 * 10;
                            }
                            break;
                        case 1:
                            if (line.substr(i, 3) == "two")
                            {
                                current += 2 * 10;
                            }
                            else if (line.substr(i, 5) == "three")
                            {
                                current += 3 * 10;
                            }
                            break;
                        case 2:
                            if (line.substr(i, 4) == "four")
                            {
                                current += 4 * 10;
                            }
                            else if (line.substr(i, 4) == "five")
                            {
                                current += 5 * 10;
                            }
                            break;
                        case 3:
                            if (line.substr(i, 3) == "six")
                            {
                                current += 6 * 10;
                            }
                            else if (line.substr(i, 5) == "seven")
                            {
                                current += 7 * 10;
                            }
                            break;
                        case 4:
                            if (line.substr(i, 5) == "eight")
                            {
                                current += 8 * 10;
                            }
                            break;
                        case 5:
                            if (line.substr(i, 4) == "nine")
                            {
                                current += 9 * 10;
                            }
                            break;
                    }
                    if (current != 0) { break; } // in case of succesful written number found, break
                }
                catch (const std::out_of_range & e)
                {
                    // ignore
                }
            }
            else if (isdigit(line[i]))
            {
                current += (line[i] - '0') * 10;
                break;
            }
        }
        for (int i = line.size() - 1; i >= 0; i--)
        {
            std::string lastChars = "eorxnt";
            auto it = lastChars.find(line[i]); // check if current char is last char of a written number

            int tmp = current;
            if (it != std::string::npos)
            {
                try {
                    switch (it)
                    {
                        case 0:
                            if (line.substr(i-2, 3) == "one")
                            {
                                current += 1;
                            }
                            else if (line.substr(i-4, 5) == "three")
                            {
                                current += 3;
                            }
                            else if (line.substr(i-3, 4) == "five")
                            {
                                current += 5;
                            }
                            else if (line.substr(i-3, 4) == "nine")
                            {
                                current += 9;
                            }
                            break;
                        case 1:
                            if (line.substr(i-2, 3) == "two")
                            {
                                current += 2;
                            }
                            break;
                        case 2:
                            if (line.substr(i-3, 4) == "four")
                            {
                                current += 4;
                            }
                            break;
                        case 3:
                            if (line.substr(i-2, 3) == "six")
                            {
                                current += 6;
                            }
                            break;
                        case 4:
                            if (line.substr(i-4, 5) == "seven")
                            {
                                current += 7;
                            }
                            break;
                        case 5:
                            if (line.substr(i-4, 5) == "eight")
                            {
                                current += 8;
                            }
                            break;
                    }
                    if (current != tmp) { break; } // in case of succesful written number found, break
                }
                catch (const std::out_of_range & e)
                {
                    // ignore
                }

            }
            else if (isdigit(line[i]))
            {
                current += (line[i] - '0');
                break;
            }
        }
        result += current;
    }
    
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest1("input-files/2023/day01_testinput1.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest1.getBuffer(), '\n');
    assert(part1(testInput) == 142);

    FileHandler fileHandler("input-files/2023/day01.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), '\n');

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;


    FileHandler fileHandlerTest2("input-files/2023/day01_testinput2.txt");
    std::vector<std::string> testInput2 = StringParser::toVector(fileHandlerTest2.getBuffer(), '\n');
    assert(part2(testInput2) == 281);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}