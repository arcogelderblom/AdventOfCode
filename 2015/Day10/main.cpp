#include <iostream>
#include <cassert>

#include "StringParser.hpp"
#include "FileHandler.hpp"

std::string generateNext(const std::string & sequence)
{
    std::string next;
    char current = sequence[0];
    int count = 0;
    for (const char & c : sequence)
    {
        if (c != current)
        {
            next += std::to_string(count);
            next += current;
            count = 0;
        }
        current = c;
        count += 1;
    }

    next += std::to_string(count);
    next += current;
    return next;
}

int part1(std::vector<std::string> input)
{
    std::string sequence = input[0];
    for (int i = 0; i < 40; i++)
    {
        sequence = generateNext(sequence);
    }
    return sequence.length();
}

int part2(std::vector<std::string> input)
{
    std::string sequence = input[0];
    for (int i = 0; i < 50; i++)
    {
        sequence = generateNext(sequence);
    }
    return sequence.length();
}

int main(void) 
{
    FileHandler fileHandler("input-files/2015/day10.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}