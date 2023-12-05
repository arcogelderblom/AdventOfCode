#pragma once 

#include <string>
#include <vector>

class StringParser
{
public:
    static std::vector<std::string> toVector(std::string src, const std::string & delimiter);
    static std::vector<int> toIntVector(std::string src, const std::string & delimiter);
    static std::vector<long long> toLongLongVector(std::string src, const std::string & delimiter);
};