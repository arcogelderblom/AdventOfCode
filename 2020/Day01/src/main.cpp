#include <iostream>
#include <algorithm>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::vector<int> stringVecToIntVec(std::vector<std::string> input) {
    std::vector<int> result;
    for (std::string line : input) {
        result.push_back(std::stoi(line));
    }
    return result;
}

int puzzleOne(std::vector<int> input) {
    std::sort(input.begin(), input.end());

    for (int i = input.size()-1; i >= 0; i--) {
        for (int number : input) {
            if (input[i] + number == 2020) {
                return input[i] * number;
            }
            else if (input[i] + number > 2020) {
                break;
            }
        }
    }

    return 0;
}

int puzzleTwo(std::vector<int> input) {
    for (int i = 0; i < input.size()-3; i++) {
        for (int j = i+1; j < input.size()-2; j++) {
            for (int k = input.size()-1; k >= j; k--) {
                if (input[i] + input[j] + input[k] == 2020) {
                    return input[i] * input[j] * input[k];
                }
            }
        }
    }

    return 0;
}

int main(void) {
    FileHandler fileHandler("input-files/2020/day01.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    std::cout << "Puzzle one: " << puzzleOne(stringVecToIntVec(input)) << std::endl;
    std::cout << "Puzzle two: " << puzzleTwo(stringVecToIntVec(input)) << std::endl;

    return 0;
}