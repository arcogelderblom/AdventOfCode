#pragma once

class Cup {
private:
    int _num;
public:
    Cup* next;
    Cup(int num);
    int getNum();

    friend bool operator==(const Cup& lhs, const Cup& rhs) {
        return lhs._num == rhs._num;
    }
};