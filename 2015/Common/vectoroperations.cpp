#include "vectoroperations.hpp"

#include "stringoperations.hpp"

std::vector< std::vector<std::string> > VectorOperations::splitVectorInSubVectors(std::vector<std::string> vector, std::string delimiter)
{
    std::vector< std::vector<std::string> > result;
    for (std::string item : vector)
    {
        result.push_back(StringOperations::splitString(item, delimiter));
    }
    return result;
}

std::vector<int> VectorOperations::stringVectorToIntVector(std::vector<std::string> stringVector)
{
    std::vector<int> result;
    for (std::string item : stringVector)
    {
        result.push_back(std::stoi(item));
    }
    return result;
}

std::vector< std::vector<int> > VectorOperations::stringVectorToSeparatedIntVector(std::vector<std::string> stringVector)
{
    std::vector< std::vector<int> > result;
    for (std::string line : stringVector)
    {
        result.push_back(StringOperations::splitStringIntoSeparateNum(line));
    }
    return result;
}