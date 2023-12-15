#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <utility>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

void tilt(std::vector<std::string> & input)
{
    std::vector<std::string> output;
    for (int i = 0; i < input[0].size(); i++)
    {
        std::string currentVerticalSlice;
        for (int j = 0; j < input.size(); j++)
        {
            currentVerticalSlice += input[j][i];
        }
        int lastIndexToRollTo = 0;
        for (int i = 0; i < currentVerticalSlice.size(); i++)
        {
            if (currentVerticalSlice[i] == 'O')
            {
                if (i == lastIndexToRollTo)
                {
                    lastIndexToRollTo++;
                }
                else 
                {
                    currentVerticalSlice[lastIndexToRollTo] = 'O';
                    currentVerticalSlice[i] = '.';
                    lastIndexToRollTo += 1;
                }
            }
            else if (currentVerticalSlice[i] == '#')
            {
                lastIndexToRollTo = i + 1;
            }
        }
        output.push_back(currentVerticalSlice);
    }

    for (int i = 0; i < output[0].size(); i++)
    {
        for (int j = 0; j < output.size(); j++)
        {
            input[j][i] = output[i][j];
        }
    }
}

int getLoad(const std::vector<std::string> & input)
{
    int result = 0;
    std::vector<std::string> output;
    for (int i = 0; i < input[0].size(); i++)
    {
        std::string verticalSlice;
        for (int j = 0; j < input.size(); j++)
        {
            verticalSlice += input[j][i];
        }

        for (int i = 0; i < verticalSlice.size(); i++)
        {
            if (verticalSlice[i] == 'O')
            {
                result += verticalSlice.size() - i;
            }
        }
    }
    return result;
}

std::vector<std::string> rotateRight(const std::vector<std::string> & input)
{
    std::vector<std::string> output;
    for (int i = 0; i < input[0].size(); i++)
    {
        std::string currentSlice;
        for (int j = 0; j < input.size(); j++)
        {
            currentSlice = input[j][i] + currentSlice;
        }
        
        output.push_back(currentSlice);
    }
    return output;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<std::string> copy = input;
    tilt(copy);
    result = getLoad(copy);
    return result;
}

void performCycle(std::vector<std::string> & input)
{
    for (int i = 0; i < 4; i++)
    {
        tilt(input);
        input = rotateRight(input);
    }
}

long long part2(const std::vector<std::string> & input, long long cycles) 
{
    long long result = 0;
    std::vector<std::string> copy = input;
    std::map<std::string, int> alreadySeen;
    int repetition = 0;
    int repetitionStartCycle = 0;
    for (int i = 1; i < cycles; i++)
    {
        performCycle(copy);
        std::string stringified;
        for (const auto &line : copy) { stringified += line + '\n'; }
        stringified.pop_back(); // remove last newline char
        if (alreadySeen.find(stringified) == alreadySeen.end())
        {
            alreadySeen[stringified] = i;
        }
        else
        {
            // repeating cycle 
            repetition = i - alreadySeen[stringified];
            repetitionStartCycle = alreadySeen[stringified];
            break;
        }
    }

    for (const std::pair<std::string , int> elem : alreadySeen)
    {
        if (elem.second == ((cycles - repetitionStartCycle) % repetition) + repetitionStartCycle)
        {
            result = getLoad(StringParser::toVector(elem.first, "\n"));
            break;
        }
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day14_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 136);

    FileHandler fileHandler("input-files/2023/day14.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    assert(part2(testInput, 1000000000) == 64);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 2: " << std::flush << part2(input, 1000000000) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}