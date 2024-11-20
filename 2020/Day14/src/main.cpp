#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "Decoder.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day14.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    Decoder decoder(input, 1);
    std::cout << "Puzzle one output: " << decoder.getSumOfMemoryValues() << std::endl;

    Decoder decoder2(input, 2);
    std::cout << "Puzzle two output: " << decoder2.getSumOfMemoryValues() << std::endl;
}
