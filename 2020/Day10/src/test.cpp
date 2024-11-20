#include <iostream>
#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"
#include "AdapterStacker.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day10_testinput.txt");
    std::vector<std::string> adapterJolts = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    AdapterStacker adapterStacker(adapterJolts);
    
    assert(adapterStacker.getAmountDifference(1) == 22);
    assert(adapterStacker.getAmountDifference(3) == 10);
    assert(adapterStacker.getAmountDifference(1) * adapterStacker.getAmountDifference(3) == 220);

    assert(adapterStacker.getAmountOfOptions() == 19208);
}