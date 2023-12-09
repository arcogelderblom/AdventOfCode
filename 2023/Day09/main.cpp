#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool allZeroes(const std::vector<long long> values)
{
    for (const long long & value : values)
    {
        if (value != 0)
        {
            return false;
        }
    }
    return true;
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    for (const std::string & line : input)
    {
        std::vector<long long> values = StringParser::toLongLongVector(line, " ");
        std::vector<std::vector<long long>> sequences;
        sequences.push_back(values);
        while (!allZeroes(*(sequences.rbegin())))
        {
            int currentSequence = sequences.size() - 1;
            std::vector<long long> newSequence;
            for (int i = 1; i < sequences[currentSequence].size(); i++)
            {
                newSequence.push_back(sequences[currentSequence][i] - sequences[currentSequence][i - 1]);
            }
            sequences.push_back(newSequence);
        }
        
        sequences[sequences.size() - 1].push_back(0);
        for (int i = sequences.size() - 2; i >= 0; i--)
        {
            sequences[i].push_back(*(sequences[i].rbegin()) + *(sequences[i + 1].rbegin()));
        }
        result += *sequences[0].rbegin();
    }

    
    return result;
}
long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;
    for (const std::string & line : input)
    {
        std::vector<long long> values = StringParser::toLongLongVector(line, " ");
        std::vector<std::vector<long long>> sequences;
        sequences.push_back(values);
        while (!allZeroes(*(sequences.rbegin())))
        {
            int currentSequence = sequences.size() - 1;
            std::vector<long long> newSequence;
            for (int i = 1; i < sequences[currentSequence].size(); i++)
            {
                newSequence.push_back(sequences[currentSequence][i] - sequences[currentSequence][i - 1]);
            }
            sequences.push_back(newSequence);
        }
        
        sequences[sequences.size() - 1].insert(sequences[sequences.size() - 1].begin(), 0);
        
        for (int i = sequences.size() - 2; i >= 0; i--)
        {
            sequences[i].insert(sequences[i].begin(), sequences[i].front() - sequences[i + 1].front());
        }
        result += sequences.front().front();
    }
    
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day09_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 114);

    FileHandler fileHandler("input-files/2023/day09.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 2);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}