#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "Bag.hpp"
#include "LuggageProcessor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day07.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    LuggageProcessor processor(input);
    std::cout << "Puzzle one output: " << processor.getColorPossibilitiesFor("shiny gold") << std::endl;
    
    std::cout << "Puzzle two output: " << processor.getAmountBagsInBag("shiny gold") << std::endl;
}