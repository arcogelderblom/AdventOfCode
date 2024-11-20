#include <iostream>

#include "MemoryGame.hpp"

int main(void) {
    std::vector<std::string> input = {"18", "8", "0", "5", "4", "1", "20"};
    
    MemoryGame memoryGame(input);
    std::cout << "Puzzle one output: " << memoryGame.getNumberSpoken(2020) << std::endl;
    std::cout << "Puzzle two output: " << memoryGame.getNumberSpoken(30000000) << std::endl;
}
