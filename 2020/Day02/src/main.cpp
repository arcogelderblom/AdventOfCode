#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"
#include "PasswordValidator.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day02.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    int validPasswords = 0;
    PasswordValidator validator;
    for (std::string line : input) {
        if (validator.checkValidityPuzzleOne(line)) {
            validPasswords++;
        }
    }

    std::cout << "Puzzle one output: " << validPasswords << std::endl;

    validPasswords = 0; // reset variable
    for (std::string line : input) {
        if (validator.checkValidityPuzzleTwo(line)) {
            validPasswords++;
        }
    }
    std::cout << "Puzzle two output: " << validPasswords << std::endl;
}