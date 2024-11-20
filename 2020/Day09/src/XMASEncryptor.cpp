#include "XMASEncryptor.hpp"

#include <numeric>

XMASEncryptor::XMASEncryptor(std::vector<std::string> XMASData) {
    parse(XMASData);
}

void XMASEncryptor::parse(std::vector<std::string> XMASData) {
    for (std::string number : XMASData) {
        _XMASData.push_back(std::stol(number));
    }
}

long XMASEncryptor::getIncorrectNumber() {
    for (long i = 0; i+26 < _XMASData.size(); i++) {
        std::vector<long> preamble;
        preamble.insert(preamble.end(), _XMASData.begin() + i, _XMASData.begin() + i + 25);

        if (!isSumOf2(_XMASData[i+25], preamble)) {
            return _XMASData[i+25];
        }
    }
    return 0;
}

long XMASEncryptor::getEncryptionWeakness() {
    long incorrectNumber = getIncorrectNumber();
    for (int amountOfNumbers = 2; ; amountOfNumbers++) {
        for (long i = 0; i+amountOfNumbers < _XMASData.size(); i++) {
            std::vector<long> preamble;
            preamble.insert(preamble.end(), _XMASData.begin() + i, _XMASData.begin() + i + amountOfNumbers);

            if (std::accumulate(preamble.begin(), preamble.end(), 0) == incorrectNumber) {
                std::sort(preamble.begin(), preamble.end());
                return preamble[0] + preamble[amountOfNumbers-1];
            }
        }
    }
    return 0;
}

bool XMASEncryptor::isSumOf2(long result, std::vector<long> preamble) {
    for (long i = 0; i < preamble.size(); i++) {
        for (long j = 0; j < preamble.size(); j++) {
            if (i == j) {
                continue; // do nothing
            }
            else if (preamble[i] + preamble[j] == result) {
                return true;
            }
        }
    }
    return false;
}