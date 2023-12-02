#include <iostream>
#include <cassert>
#include <chrono>

#include "FileHandler.hpp"
#include "StringParser.hpp"
#include "submarine.hpp"

int main(void)
{
    std::vector<std::string> testInput {"forward 5", "down 5", "forward 8", "up 3", "down 8", "forward 2"};
    Submarine testInputSubmarine;
    testInputSubmarine.travel(testInput);
    assert(testInputSubmarine.getHorizontalPosition() * testInputSubmarine.getDepth() == 150);

    FileHandler fileHandler("input-files/2021/day02.txt");
    std::vector<std::string> commands = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    Submarine submarine;
    submarine.travel(commands);
    std::cout << "Day 2, puzzle 1: " << std::flush << submarine.getHorizontalPosition() * submarine.getDepth() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    Submarine testInputSubmarine2;
    testInputSubmarine2.travel(testInput, true);
    assert(testInputSubmarine2.getHorizontalPosition() * testInputSubmarine2.getDepth() == 900);

    t_begin = std::chrono::high_resolution_clock::now();
    Submarine submarine2;
    submarine2.travel(commands, true);
    std::cout << "Day 2, puzzle 2: " << std::flush << submarine2.getHorizontalPosition() * submarine2.getDepth() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}