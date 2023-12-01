#pragma once 

#include <string>
#include <vector>

class StringParser
{
public:
    static std::vector<std::string> toVector(const std::string & src, const char & delimiter);
};