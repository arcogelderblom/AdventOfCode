#include "PassportValidator.hpp"

#include <iostream>
#include <vector>

bool PassportValidator::validate(std::string passport) {
    if (passport.find("byr") == std::string::npos ||
        passport.find("iyr") == std::string::npos ||
        passport.find("eyr") == std::string::npos ||
        passport.find("hgt") == std::string::npos ||
        passport.find("hcl") == std::string::npos ||
        passport.find("ecl") == std::string::npos ||
        passport.find("pid") == std::string::npos) {
        return false;
    }
    return true;
}

bool PassportValidator::validate(Passport passport) {
    // check birth year
    std::string byr = passport.getBirthYear();
    if (byr.length() != 4) {
        return false;
    }
    if (!std::isdigit(byr[0]) ||
        !std::isdigit(byr[1]) ||
        !std::isdigit(byr[2]) ||
        !std::isdigit(byr[3])) {
        return false;
    }
    if (std::stoi(byr) < 1920 || std::stoi(byr) > 2002) {
        return false;
    }
    
    // check issue year
    std::string iyr = passport.getIssueYear();
    if (iyr.length() != 4) {
        return false;
    }
    if (!std::isdigit(iyr[0]) ||
        !std::isdigit(iyr[1]) ||
        !std::isdigit(iyr[2]) ||
        !std::isdigit(iyr[3])) {
        return false;
    }
    if (std::stoi(iyr) < 2010 || std::stoi(iyr) > 2020) {
        return false;
    }

    // check expiration year
    std::string eyr = passport.getExpirationYear();
    if (eyr.length() != 4) {
        return false;
    }
    if (!std::isdigit(eyr[0]) ||
        !std::isdigit(eyr[1]) ||
        !std::isdigit(eyr[2]) ||
        !std::isdigit(eyr[3])) {
        return false;
    }
    if (std::stoi(eyr) < 2020 || std::stoi(eyr) > 2030) {
        return false;
    }

    // check height
    std::string height = passport.getHeight();
    if (height.find("cm") != std::string::npos && height.length() == 5) {
        int num = std::stoi(height.substr(0, 3));
        if (num < 150 || num > 193) {
            return false;
        }
    }
    else if (height.find("in") != std::string::npos && height.length() == 4) {
        int num = std::stoi(height.substr(0, 2));
        if (num < 59 || num > 76) {
            return false;
        }
    }
    else {
        return false;
    }

    // check hair color
    std::string hairColor = passport.getHairColor();
    if (hairColor[0] != '#' || hairColor.length() != 7) {
        return false;
    }
    for (int i = 1; i < hairColor.length(); i++) {
        if (!std::isxdigit(hairColor[i])) {
            return false;
        }
    }

    // check eye color
    std::string eyeColor = passport.getEyeColor();
    std::vector<std::string> eyeColorOptions = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    bool found = false;
    for (std::string color : eyeColorOptions) {
        if (eyeColor == color) {
            found = true;
            break;
        }
    }
    if (!found) {
        return false;
    }

    // check passport id
    std::string passportId = passport.getPassportID();
    if (passportId.length() != 9) {
        return false;
    }
    for (char c : passportId) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}