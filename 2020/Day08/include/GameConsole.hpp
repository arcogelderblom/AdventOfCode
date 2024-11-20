#pragma once

#include <string>
#include <vector>

enum Operation {
    acc,
    jmp,
    nop
};

struct Instruction {
    Operation operation;
    int argument;
};

class GameConsole {
private:
    int accumulator;
    std::vector<Instruction> instructions;
    std::vector<int> visitedInstructions;
    void parse(std::vector<std::string> code);
public:
    GameConsole(std::vector<std::string> code);
    bool findLoop();
    int getAccumulator();
    void fixLoop();
    void play();
};