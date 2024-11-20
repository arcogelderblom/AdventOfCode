#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "XMASEncryptor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day09.txt");
    std::vector<std::string> XMASdata = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    XMASEncryptor encryptor(XMASdata);
    std::cout << "Puzzle one output: " << encryptor.getIncorrectNumber() << std::endl;
    
    std::cout << "Puzzle two output: " << encryptor.getEncryptionWeakness() << std::endl;
}