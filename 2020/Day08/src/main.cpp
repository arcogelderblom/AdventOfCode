#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "GameConsole.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day08.txt");
    std::vector<std::string> bootcode = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    GameConsole console(bootcode);
    console.findLoop();
    std::cout << "Puzzle one output: " << console.getAccumulator() << std::endl;
    
    console.fixLoop();
    console.play();
    std::cout << "Puzzle two output: " << console.getAccumulator() << std::endl;
}