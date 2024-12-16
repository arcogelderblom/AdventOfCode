#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include "StringParser.hpp"
#include "FileHandler.hpp"

#include "md5.hpp"

int getLowestPossibleNum5Zeroes(const std::string& base)
{
    int num = 100000; // educated guess
    std::string hash = "abcde";
    while (!(hash[0] == '0' &&
            hash[1] == '0' &&
            hash[2] == '0' &&
            hash[3] == '0' &&
            hash[4] == '0'))
    {
        num++;
        hash = md5(base + std::to_string(num));
    }
    return num;
}

int getLowestPossibleNum6Zeroes(const std::string& base)
{
    int num = 1000000; // educated guess
    std::string hash = "abcdef";
    while (!(hash[0] == '0' &&
            hash[1] == '0' &&
            hash[2] == '0' &&
            hash[3] == '0' &&
            hash[4] == '0' &&
            hash[5] == '0'))
    {
        num++;
        hash = md5(base + std::to_string(num));
    }
    
    return num;
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day04.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 1: " << std::flush << getLowestPossibleNum5Zeroes(input[0]) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 2: " << std::flush << getLowestPossibleNum6Zeroes(input[0]) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}