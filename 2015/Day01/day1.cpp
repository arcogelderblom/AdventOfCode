#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include "StringParser.hpp"
#include "FileHandler.hpp"


int getFloor(std::string instruction)
{
    return std::count(instruction.begin(), instruction.end(), '(') - std::count(instruction.begin(), instruction.end(), ')');
}

int getPositionBasement(std::string instruction)
{
    int floor = 0;
    for (int i = 0; i < instruction.size(); i++)
    {
        floor = instruction[i] == '(' ? floor + 1 : floor - 1;
        if (floor == -1)
        {
            return i + 1; // we want pos, not index
        }
    }
    return -1;
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day01.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << getFloor(input[0]) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << getPositionBasement(input[0]) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}