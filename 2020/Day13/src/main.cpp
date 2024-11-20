#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "BusPlanner.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day13.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    BusPlanner planner(input[1]);
    std::cout << "Puzzle one output: " << planner.puzzleOne(std::stoi(input[0])) << std::endl;
    std::cout << "Puzzle two output: " << planner.puzzleTwo() << std::endl;
}
