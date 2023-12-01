#include "FileHandler.hpp"

#include <sstream>
#include <fstream>

FileHandler::FileHandler(const std::string & filePath)
{
    std::ifstream inputFile(filePath);
    std::stringstream stringStream;
    stringStream << inputFile.rdbuf();
    _buffer = stringStream.str();
}

std::string FileHandler::getBuffer()
{
    return _buffer;
}
