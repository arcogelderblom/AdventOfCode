#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"
#include "PassportValidator.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day04.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
    for (std::string & line : input) {
        while (line.find('\n') != std::string::npos) {
            line.replace(line.find('\n'), 1, " ");   
        }
    }

    PassportValidator validator;
    int validPassports = 0;
    for (std::string passport : input) {
        if (validator.validate(passport)) {
            validPassports++;
        }
    }

    std::cout << "Puzzle one output: " << validPassports << "/" << input.size() << std::endl;

    validPassports = 0;
    for (std::string passportAsString : input) {
        if (validator.validate(passportAsString)) {
            Passport passport(passportAsString);
            if (validator.validate(passport)) {
                validPassports++;
            }
        }
    }

    std::cout << "Puzzle two output: " << validPassports << "/" << input.size() << std::endl;

}