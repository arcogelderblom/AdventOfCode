#include <iostream>
#include <cassert>

#include <map>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int part1(std::vector<std::string> input)
{
    int result = 0;
    std::string currentNum;
    for (const char & c : input[0])
    {
        if (isdigit(c) || c == '-')
        {
            currentNum += c;
        }
        else
        {
            if (!currentNum.empty())
            {
                result += std::stoi(currentNum);
                currentNum = "";
            }
        }
    }
    return result;
}

int sum(std::string json, int & index)
{
    int count = 0;
    std::string currentNum;
    bool object = false;

    if (json[index] == '{')
    {
        object = true;
    }
    index++;
    while (index < json.size())
    {
        if ((object && json[index] == '}') || (!object && json[index] == ']') )
        {
            if (!currentNum.empty())
            {
                count += std::stoi(currentNum);
                currentNum = "";
            }
            return count;
        }
        else if (json[index] == '{' || json[index] == '[')
        {
            count += sum(json, index);
        }
        else if (object && json[index] == 'r' && json[index+1] == 'e' && json[index+2] == 'd')
        {
            // fast forward to end of *this* object and return 0
            int depth = 0;
            while (json[index] != '}' || depth > 0)
            {
                if (json[index] == '{') { depth++;}
                if (json[index] == '}') { depth--;}
                index++;
            }
            return 0;
        }
        else if (isdigit(json[index]) || json[index] == '-')
        {
            currentNum += json[index];
        }
        else
        {
            if (!currentNum.empty())
            {
                count += std::stoi(currentNum);
                currentNum = "";
            }
        }
        index++;
    }

    return 0;
}

int part2(std::vector<std::string> input)
{
    int result = 0;
    int index = 0;
    result = sum(input[0], index);
    
    return result;
}

int main(void) 
{
    FileHandler fileHandler("input-files/2015/day12.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}