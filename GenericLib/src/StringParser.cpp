#include "StringParser.hpp"

#include <sstream>

std::vector<std::string> StringParser::toVector(const std::string & src, const char & delimiter)
{
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(src);
    while(std::getline(ss, line, delimiter)) {
        vec.push_back(line);
    }
    return vec;
}