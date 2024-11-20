#include "GameConsole.hpp"

 #include <iostream>

GameConsole::GameConsole(std::vector<std::string> code) {
    parse(code);
}

void GameConsole::parse(std::vector<std::string> code) {
    for (std::string instruction : code) {
        Instruction newInstruction;
        std::string operation = instruction.substr(0, 3);
        if (operation == "acc") {
            newInstruction.operation = acc;
        }
        else if (operation == "jmp") {
            newInstruction.operation = jmp;
        }
        else if (operation == "nop") {
            newInstruction.operation = nop;
        }
        newInstruction.argument = std::stoi(instruction.substr(3));
        instructions.push_back(newInstruction);
    }
}

bool GameConsole::findLoop() {
    accumulator = 0;

    visitedInstructions = std::vector<int>();
    int curIndex = 0;
    while (std::find(visitedInstructions.begin(), visitedInstructions.end(), curIndex) == visitedInstructions.end() && curIndex < instructions.size()) {
        visitedInstructions.push_back(curIndex);
        switch(instructions[curIndex].operation) {
            case acc:
                accumulator += instructions[curIndex].argument;
                curIndex++;
                break;
            case jmp:
                curIndex += instructions[curIndex].argument;
                break;
            case nop:
                curIndex++;
                break;
        }
    }
    if (curIndex >= instructions.size()) {
        return false;
    }
    return true;
}

int GameConsole::getAccumulator() {
    return accumulator;
}

void GameConsole::fixLoop() {
    if (visitedInstructions.empty()) {
        findLoop();
    }
    for (auto i = visitedInstructions.rbegin(); i != visitedInstructions.rend(); i++) {
        Instruction & faultyInstruction = instructions[*i];
        if (faultyInstruction.operation == jmp) {
            faultyInstruction.operation = nop;
            if (!findLoop()) {
                return;
            }
            faultyInstruction.operation = jmp;
        }
        else if (faultyInstruction.operation == nop) {
            faultyInstruction.operation = jmp;
            if (!findLoop()) {
                return;
            }
            faultyInstruction.operation = nop;
        }
    }
}

void GameConsole::play() {
    int accumulator = 0;

    int curIndex = 0;
    while (curIndex < instructions.size() && curIndex >= 0) {
        switch(instructions[curIndex].operation) {
            case acc:
                accumulator += instructions[curIndex].argument;
                curIndex++;
                break;
            case jmp:
                curIndex += instructions[curIndex].argument;
                break;
            case nop:
                curIndex++;
                break;
        }
    }
}