#include "StringParser.hpp"

#include <sstream>

std::vector<std::string> StringParser::toVector(std::string src, const std::string & delimiter)
{
    std::vector<std::string> vec;
    while(src.find(delimiter) != std::string::npos)
    {
        if (src.find(delimiter) == 0) 
        {

        src = src.substr(delimiter.size());
        }
        else
        {
            vec.push_back(src.substr(0, src.find(delimiter)));
            src = src.substr(src.find(delimiter) + delimiter.size());
        }
    }
    vec.push_back(src);
    return vec;
}

std::vector<int> StringParser::toIntVector(std::string src, const std::string & delimiter)
{
    std::vector<std::string> vec = StringParser::toVector(src, delimiter);
    std::vector<int> result;
    for(const std::string & item : vec)
    {
        result.push_back(std::stoi(item));
    }
    return result;
}