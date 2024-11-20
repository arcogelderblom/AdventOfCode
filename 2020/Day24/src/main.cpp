#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "Floor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day24.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    Floor floor(input);
    std::cout << "Puzzle one output: " << floor.getBlackTiles().size() << std::endl;
    floor.processDays(100);
    std::cout << "Puzzle two output: " << floor.getBlackTiles().size() << std::endl;
}
