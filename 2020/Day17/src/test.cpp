#include <iostream>
#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "ConwayCubesV1.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day17_testinput.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    ConwayCubesV1 conwayCubes(input);
    conwayCubes.cycle(6);
    assert(conwayCubes.getActiveCubes() == 112);
}
