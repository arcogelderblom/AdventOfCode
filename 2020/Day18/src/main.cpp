#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "Calculator.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day18.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    long long sum = 0;
    for (std::string expression : input) {
        Calculator calculator(expression);
        sum += calculator.getAnswer(1);
    }
    std::cout << "Puzzle one output: " << sum << std::endl;

    sum = 0;
    for (std::string expression : input) {
        Calculator calculator(expression);
        sum += calculator.getAnswer(2);
    }
    std::cout << "Puzzle two output: " << sum << std::endl;
}
