#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

void getNextNumber(long long & secretNumber)
{
    long long value = secretNumber * 64;
    secretNumber ^= value;
    secretNumber %= 16777216;
    value = secretNumber / 32;
    secretNumber ^= value;
    secretNumber %= 16777216;
    value = secretNumber * 2048;
    secretNumber ^= value;
    secretNumber %= 16777216;

}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    for (const std::string & line : input)
    {
        long long secretNumber = std::stoll(line);
        for (int i = 0; i < 2000; i++)
        {
            getNextNumber(secretNumber);
        }
        result += secretNumber;
    }
    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::map<std::vector<int>, long long> sequencesAndTotalPrice;
    // std::set<std::vector<int>> uniqueSequences;
    for (const std::string & line : input)
    {
        long long secretNumber = std::stoll(line);
        int bananaPrice = secretNumber % 10;
        std::vector<int> currentSequence;
        std::set<std::vector<int>> uniqueSequences;
        for (int i = 0; i < 2000; i++)
        {
            getNextNumber(secretNumber);
            int newBananaPrice = secretNumber % 10;
            int diff = newBananaPrice - bananaPrice;
            currentSequence.push_back(diff);
            if (currentSequence.size() >= 4)
            {
                if (currentSequence.size() > 4)
                {
                    currentSequence.erase(currentSequence.begin());
                }
                if (uniqueSequences.find(currentSequence) == uniqueSequences.end())
                {
                    uniqueSequences.insert(currentSequence);
                    sequencesAndTotalPrice[currentSequence] += newBananaPrice;
                }
            }
            bananaPrice = newBananaPrice;
        }
    }

    for (const std::pair<std::vector<int>, long long> & sequenceAndTotalPrice : sequencesAndTotalPrice)
    {
        if (sequenceAndTotalPrice.second > result)
        {
            result = sequenceAndTotalPrice.second;
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day22_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput) == 37327623);

    FileHandler fileHandler("input-files/2024/day22.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 22, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    FileHandler testFileHandler2("input-files/2024/day22_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n");
    assert(part2(testinput2) == 23);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 22, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}