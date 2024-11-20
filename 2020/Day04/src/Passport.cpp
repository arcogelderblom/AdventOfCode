#include "Passport.hpp"

#include <iostream>

Passport::Passport(std::string passport) {
    parse(passport);
}

void Passport::parse(std::string passport) {
    _birthYear = passport.substr(passport.find("byr:")+std::string("byr:").length(), passport.find(" ", passport.find("byr:")) - (passport.find("byr:") + std::string("byr:").length()));
    _issueYear = passport.substr(passport.find("iyr:")+std::string("iyr:").length(), passport.find(" ", passport.find("iyr:")) - (passport.find("iyr:") + std::string("iyr:").length()));
    _expirationYear = passport.substr(passport.find("eyr:")+std::string("eyr:").length(), passport.find(" ", passport.find("eyr:")) - (passport.find("eyr:") + std::string("eyr:").length()));
    _height = passport.substr(passport.find("hgt:")+std::string("hgt:").length(), passport.find(" ", passport.find("hgt:")) - (passport.find("hgt:") + std::string("hgt:").length()));
    _hairColor = passport.substr(passport.find("hcl:")+std::string("hcl:").length(), passport.find(" ", passport.find("hcl:")) - (passport.find("hcl:") + std::string("hcl:").length()));
    _eyeColor = passport.substr(passport.find("ecl:")+std::string("ecl:").length(), passport.find(" ", passport.find("ecl:")) - (passport.find("ecl:") + std::string("ecl:").length()));
    _passportID = passport.substr(passport.find("pid:")+std::string("pid:").length(), passport.find(" ", passport.find("pid:")) - (passport.find("pid:") + std::string("pid:").length()));
}

std::string Passport::getBirthYear() {
    return _birthYear;
}

std::string Passport::getIssueYear() {
    return _issueYear;
}

std::string Passport::getExpirationYear() {
    return _expirationYear;
}

std::string Passport::getHeight() {
    return _height;
}

std::string Passport::getHairColor() {
    return _hairColor;
}

std::string Passport::getEyeColor() {
    return _eyeColor;
}

std::string Passport::getPassportID() {
    return _passportID;
}
