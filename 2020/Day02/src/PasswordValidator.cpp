#include "PasswordValidator.hpp"

#include <iostream>
#include <algorithm>

bool PasswordValidator::checkValidityPuzzleOne(std::string passwordWithPolicy) {
    std::string policy(passwordWithPolicy.begin(), std::find(passwordWithPolicy.begin(), passwordWithPolicy.end(), ':'));

    std::string amount(policy.begin(), std::find(policy.begin(), policy.end(), ' '));
    int min = std::stoi(std::string(policy.begin(), std::find(policy.begin(), policy.end(), '-')));
    int max = std::stoi(std::string(std::find(policy.begin(), policy.end(), '-') + 1, policy.end()));
    char character = policy[policy.size() - 1];

    std::string password(std::find(passwordWithPolicy.begin(), passwordWithPolicy.end(), ':') + 2, passwordWithPolicy.end()); // +2 because of the space following ':'
    
    int count = 0;
    for (char c : password) {
        if (c == character) {
            count += 1;
        }
        if (count > max) {
            return false;
        }
    }

    if (count >= min) {
        return true;
    }
    return false;
}

bool PasswordValidator::checkValidityPuzzleTwo(std::string passwordWithPolicy) {
    std::string policy(passwordWithPolicy.begin(), std::find(passwordWithPolicy.begin(), passwordWithPolicy.end(), ':'));

    std::string amount(policy.begin(), std::find(policy.begin(), policy.end(), ' '));
    int first = std::stoi(std::string(policy.begin(), std::find(policy.begin(), policy.end(), '-')));
    int second = std::stoi(std::string(std::find(policy.begin(), policy.end(), '-') + 1, policy.end()));
    char character = policy[policy.size() - 1];

    std::string password(std::find(passwordWithPolicy.begin(), passwordWithPolicy.end(), ':') + 2, passwordWithPolicy.end()); // +2 because of the space following ':'
    
    // correct index since it starts at 1 instead of 0
    if (password[first-1] == password[second-1]) {
        return false;
    }
    if (password[first-1] == character || password[second-1] == character) {
        return true;
    }
    return false;
}
