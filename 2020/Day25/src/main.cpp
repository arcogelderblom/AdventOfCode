#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "Crypto.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day25.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    Crypto crypto;
    long loopSize = crypto.calculateLoopSize(std::stoll(input[0]));
    long long value = 1;
    for (int loop = 0; loop < loopSize; loop++) {
        crypto.performLoop(value, std::stoll(input[1]));
    }
    std::cout << "Puzzle one output: " << value << std::endl;
}
