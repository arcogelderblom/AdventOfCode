#pragma once

#include <string>
#include <vector>

class XMASEncryptor {
private:
    std::vector<long> _XMASData;
    void parse(std::vector<std::string> XMASData);
    bool isSumOf2(long result, std::vector<long> preamble);
public:
    XMASEncryptor(std::vector<std::string> XMASData);
    long getIncorrectNumber();
    long getEncryptionWeakness();
};