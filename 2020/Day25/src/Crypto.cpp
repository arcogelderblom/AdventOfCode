#include "Crypto.hpp"

int Crypto::calculateLoopSize(long long publicKey) {
    long subjectNumber = 7;
    long long value = 1;
    int loopSize = 0;
    while (value != publicKey) {
        loopSize += 1;
        performLoop(value, subjectNumber);
    }
    return loopSize;
}

void Crypto::performLoop(long long & value, int subjectNumber) {
    value = value * subjectNumber;
    value = value % 20201227;
}
