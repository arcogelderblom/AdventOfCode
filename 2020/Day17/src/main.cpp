#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "ConwayCubesV1.hpp"
#include "ConwayCubesV2.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day17.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    ConwayCubesV1 conwayCubes(input);
    conwayCubes.cycle(6);
    std::cout << "Puzzle one output: " << conwayCubes.getActiveCubes() << std::endl;

    ConwayCubesV2 conwayCubesV2(input);
    conwayCubesV2.cycle(6);
    std::cout << "Puzzle two output: " << conwayCubesV2.getActiveCubes() << std::endl;
}
