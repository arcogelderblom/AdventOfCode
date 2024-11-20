#pragma once

#include <string>
#include <vector>
#include <map>

class Decoder {
private:
    std::map<unsigned long, unsigned long> _memory;
    void processV1(std::vector<std::string> instructions);
    void processV2(std::vector<std::string> instructions);
    void calculateAllBinaryOptions(std::string memoryAddress, std::vector<std::string> & memoryAddresses, std::vector<int> indexesOfX, int curIndex);
public:
    Decoder(std::vector<std::string> instructions, int emulatorVersion);
    unsigned long getSumOfMemoryValues();
};