#pragma once

class Crypto {
public:
    int calculateLoopSize(long long publicKey);
    void performLoop(long long & value, int subjectNumber);
};