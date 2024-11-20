#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "NavigationComputer.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day12.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    NavigationComputer computer(input);
    std::cout << "Puzzle one output: " << computer.getManhattanDistance(1) << std::endl;

    std::cout << "Puzzle two output: " << computer.getManhattanDistance(2) << std::endl;
}
