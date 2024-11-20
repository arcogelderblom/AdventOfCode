#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "FloorPlan.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day11.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    std::vector<std::string> input2 = input;

    FloorPlan floorPlan(input);
    std::cout << "Puzzle one output: " << floorPlan.getOccupiedSeatsAmount(1) << std::endl;

    FloorPlan floorPlan2(input2);
    std::cout << "Puzzle two output: " << floorPlan2.getOccupiedSeatsAmount(2) << std::endl;
}
