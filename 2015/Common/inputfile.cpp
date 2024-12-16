#include "inputfile.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

InputFile::InputFile(std::string path)
{
    std::ifstream inputFile(path);
    std::stringstream stringStream;
    stringStream << inputFile.rdbuf();
    _fileContentBuffer = stringStream.str();
}

std::vector<int> InputFile::getContentAsInt(std::string delimiter) 
{
    std::vector<std::string> contentAsString = getContentUsingDelimiter(delimiter);
    std::vector<int> result;
    for (std::string item : contentAsString) 
    {
        result.push_back(std::stoi(item));
    }
    return result;
}

std::vector<std::string> InputFile::getContentAsString(std::string delimiter)
{
    return getContentUsingDelimiter(delimiter);
}

std::vector<std::string> InputFile::getContentUsingDelimiter(std::string delimiter)
{
    std::vector<std::string> result;
    int lastIndex = 0;
    std::string currentItem;
    for (int currentIndex = 0; currentIndex < _fileContentBuffer.size(); currentIndex++) 
    {
        if (_fileContentBuffer[currentIndex] == delimiter[0]) {
            bool delimiterFound = true;
            int i = 0;
            for (; i < delimiter.size(); i++) {
                if (_fileContentBuffer[currentIndex+i] != delimiter[i]) {
                    delimiterFound = false;;
                }
            }
            if (delimiterFound) {
                result.push_back(currentItem);
                lastIndex = currentIndex+i;
                currentIndex += i;
                currentItem = "";
            }
        }
        currentItem += _fileContentBuffer[currentIndex];
    }

    // if last one is not empty, add to list
    if (!currentItem.empty()) {
        result.push_back(currentItem);
    }

    return result;
}
