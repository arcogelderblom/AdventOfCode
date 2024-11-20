#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"
#include "AdapterStacker.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day10.txt");
    std::vector<std::string> adapterJolts = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    AdapterStacker adapterStacker(adapterJolts);
    std::cout << "Puzzle one output: " << adapterStacker.getAmountDifference(1) * adapterStacker.getAmountDifference(3) << std::endl;
    
    std::cout << "Puzzle two output: " << adapterStacker.getAmountOfOptions() << std::endl;
}