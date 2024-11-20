#pragma once

#include <string>

class Passport {
private:
    std::string _birthYear;
    std::string _issueYear;
    std::string _expirationYear;
    std::string _height;
    std::string _hairColor;
    std::string _eyeColor;
    std::string _passportID;

    void parse(std::string passport);
public:
    Passport(std::string passport);

    std::string getBirthYear();
    std::string getIssueYear();
    std::string getExpirationYear();
    std::string getHeight();
    std::string getHairColor();
    std::string getEyeColor();
    std::string getPassportID();
};