#pragma once

#include <string>

#include "Passport.hpp"

class PassportValidator {
public:
    bool validate(std::string passport);
    bool validate(Passport passport);
};