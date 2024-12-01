#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::vector<int> firstList, secondList;

    for (const std::string& line: input)
    {
        std::vector<int> split = StringParser::toIntVector(line, "   ");
        firstList.push_back(split[0]);
        secondList.push_back(split[1]);
    }

    std::sort(firstList.begin(), firstList.end());
    std::sort(secondList.begin(), secondList.end());

    for (int i = 0; i < firstList.size(); i++)
    {
        result += std::abs(firstList[i] - secondList[i]);
    }
    
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<int> firstList, secondList;

    for (const std::string& line: input)
    {
        std::vector<int> split = StringParser::toIntVector(line, "   ");
        firstList.push_back(split[0]);
        secondList.push_back(split[1]);
    }

    std::sort(firstList.begin(), firstList.end());
    std::sort(secondList.begin(), secondList.end());

    // keep track of j here so we can substract the occurences from the index to ensure we
    // do not have to process the whole of the second list each time (which we would if we
    // were to initialise the int in the for loop)
    int j = 0;
    for (int i = 0; i < firstList.size(); i++)
    {
        int occurences = 0;
        for (; secondList[j] <= firstList[i]; j++)
        {
            if (firstList[i] == secondList[j])
            {
                occurences++;
            }
        }
        j -= occurences;
        result += firstList[i] * occurences;
    }
    std::cout << result << std::endl;
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day01_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 11);

    FileHandler fileHandler("input-files/2024/day01.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 31);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}