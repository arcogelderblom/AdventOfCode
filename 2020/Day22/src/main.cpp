#include <iostream>

#include <sstream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "CombatGame.hpp"
#include "RecursiveCombatGame.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day22.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    CombatGame combatGame(input);
    std::cout << "Puzzle one output: " << combatGame.getWinningPlayerScore() << std::endl;

    RecursiveCombatGame recursiveCombatGame(input);
    std::cout << "Puzzle two output: " << recursiveCombatGame.getWinningPlayerScore() << std::endl;
}
