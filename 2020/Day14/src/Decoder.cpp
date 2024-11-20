#include "Decoder.hpp"

#include <bitset>
#include <iostream>
Decoder::Decoder(std::vector<std::string> instructions, int emulatorVersion) {
    if (emulatorVersion == 1) {
        processV1(instructions);
    }
    else if (emulatorVersion == 2) {
        processV2(instructions);
    }
}

void Decoder::processV1(std::vector<std::string> instructions) {
    std::string mask;

    for (std::string instruction : instructions) {
        if (instruction.find("mask") != std::string::npos) {
            mask = instruction.substr(7);
        }
        else {
            int memoryAddress = std::stoi(instruction.substr(instruction.find("[") + 1, instruction.find("]") - instruction.find("[")));
            std::bitset<36> value(std::stoul(instruction.substr(instruction.find("=") + 2)));
            
            // apply mask
            for (int i = mask.size()-1; i >= 0; i--) {
                if (mask[i] != 'X') {
                    value[mask.size()-1-i] = mask[i]-'0';
                }
            }

            _memory[memoryAddress] = value.to_ulong();
        }
    }
}

void Decoder::processV2(std::vector<std::string> instructions) {
    std::string mask;

    for (std::string instruction : instructions) {
        if (instruction.find("mask") != std::string::npos) {
            mask = instruction.substr(7);
        }
        else {
            std::string memoryAddressString = std::bitset<36>(std::stoul(instruction.substr(instruction.find("[") + 1, instruction.find("]") - instruction.find("[")))).to_string();
            unsigned long value = std::stoul(instruction.substr(instruction.find("=") + 2));
            
            // apply mask
            for (int i = 0; i < mask.size(); i++) {
                if (mask[i] != '0') {
                    memoryAddressString[i] = mask[i];
                }
            }

            // for all options write value to memory
            std::vector<int> indexesOfX;
            for (int i = memoryAddressString.size()-1; i >= 0 ; i--) {
                if (memoryAddressString[i] == 'X') {
                    indexesOfX.push_back(i);
                    memoryAddressString[i] = '0';
                }
            }
            std::vector<std::string> memoryAddresses;
            memoryAddresses.push_back(memoryAddressString);
            calculateAllBinaryOptions(memoryAddressString, memoryAddresses, indexesOfX, 0);

            for (std::string memoryAddress : memoryAddresses) {
                _memory[std::bitset<36>(memoryAddress).to_ulong()] = value;
            }
        }
    }
}

void Decoder::calculateAllBinaryOptions(std::string memoryAddress, std::vector<std::string> & memoryAddresses, std::vector<int> indexesOfX, int curIndex) {
    if (curIndex == indexesOfX.size()) {
        return;
    }

    memoryAddress[indexesOfX[curIndex]] = '0';
    memoryAddresses.push_back(memoryAddress);
    calculateAllBinaryOptions(memoryAddress, memoryAddresses, indexesOfX, curIndex + 1);

    memoryAddress[indexesOfX[curIndex]] = '1';
    memoryAddresses.push_back(memoryAddress);
    calculateAllBinaryOptions(memoryAddress, memoryAddresses, indexesOfX, curIndex + 1);

}

unsigned long Decoder::getSumOfMemoryValues() {
    unsigned long sum = 0;
    for (std::pair<int, unsigned long> memoryAddressValue : _memory) {
        sum += memoryAddressValue.second;
    }

    return sum;
}