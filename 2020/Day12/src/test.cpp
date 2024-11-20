#include <iostream>

#include "NavigationComputer.hpp"

int main(void) {
    std::vector<std::string> input { "F10", "N3", "F7", "R90", "F11" };
    
    NavigationComputer computer(input);
    std::cout << "Puzzle one output: " << computer.getManhattanDistance(1) << std::endl;

    std::cout << "Puzzle two output: " << computer.getManhattanDistance(2) << std::endl;
}
