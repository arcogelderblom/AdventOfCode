#include "MemoryGame.hpp"

#include <iostream>

MemoryGame::MemoryGame(std::vector<std::string> startingNumbers) {
    for (std::string startNumber : startingNumbers) {
        _spokenNumbers.push_back(std::stoi(startNumber));
    }
    for (int i = 0; i < _spokenNumbers.size(); i++) {
        _spokenNumbersByTurn[_spokenNumbers[i]] = i;
    }
}

void MemoryGame::play(int turns) {
    for (int i = _spokenNumbers.size() - 1; i < turns; i++) {
        int lastSpoken = _spokenNumbers[i];
        if (_spokenNumbersByTurn.find(lastSpoken) != _spokenNumbersByTurn.end()) {
            _spokenNumbers.push_back((i - _spokenNumbersByTurn[lastSpoken]));
        }
        else {
            _spokenNumbers.push_back(0);
        }
        _spokenNumbersByTurn[lastSpoken] = i;
    }
}

int MemoryGame::getNumberSpoken(int turn) {
    play(turn);
    return _spokenNumbers[turn-1]; // index of set turn is turn - 1
}
