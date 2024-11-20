#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"
#include "FormsProcessor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day06.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
    
    FormsProcessor processor;
    int sum = 0;
    for (std::string groupAnswers : input) {
        sum += processor.processGroup(groupAnswers, false);
    }

    std::cout << "Puzzle one output: " << sum << std::endl;

    sum = 0;
    for (std::string groupAnswers : input) {
        sum += processor.processGroup(groupAnswers, true);
    }
    std::cout << "Puzzle two output: " << sum << std::endl;
}