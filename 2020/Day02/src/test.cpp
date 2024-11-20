#include <iostream>
#include <cassert>

#include <vector>
#include "PasswordValidator.hpp"

int main(void) {
    std::vector<std::string> input{"1-3 a: abcde",
                                   "1-3 b: cdefg",
                                   "2-9 c: ccccccccc"};

    int validPasswords = 0;
    PasswordValidator validator;
    for (std::string line : input) {
        if (validator.checkValidityPuzzleOne(line)) {
            validPasswords++;
        }
    }

    assert(validPasswords == 2);

    int validPasswords2 = 0;
    for (std::string line : input) {
        if (validator.checkValidityPuzzleTwo(line)) {
            validPasswords2++;
        }
    }
    assert(validPasswords2 == 1);
}