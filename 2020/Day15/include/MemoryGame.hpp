#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class MemoryGame {
private:
    std::vector<int> _spokenNumbers;
    std::unordered_map<int, int> _spokenNumbersByTurn;
public:
    MemoryGame(std::vector<std::string> startingNumbers);
    void play(int turns);
    int getNumberSpoken(int turn);
};