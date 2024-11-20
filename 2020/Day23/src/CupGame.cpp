#include "CupGame.hpp"
#include <iostream>
CupGame::CupGame(std::string cups, int totalAmountOfCups) {
    for (char cup : cups) {
        int currentCupNum = cup - '0';
        if (currentCupNum > _highestNumCup) {
            _highestNumCup = currentCupNum;
        }
        _cups.push_back(Cup(currentCupNum));
    }
    if (totalAmountOfCups > cups.size()) {
        for (int currentCupNum = _highestNumCup + 1; currentCupNum <= totalAmountOfCups; currentCupNum++) {
            _cups.push_back(Cup(currentCupNum));
        }
        _highestNumCup = totalAmountOfCups;
    }
    for (int i = 0; i < _cups.size(); i++) {
        _cups[i].next = &_cups[i + 1];
    }
    _cups.back().next = &_cups[0];

    for (int i = 0; i < _cups.size(); i++) {
        _lookupTable[_cups[i].getNum()] = i;
    }
}

void CupGame::playRounds(int rounds) {
    Cup* currentCup = &_cups[0];
    for (int round = 1; round <= rounds; round++) {
        std::vector<int> take(3);
        auto takeCup = currentCup->next;
        take[0] = takeCup->getNum();
        takeCup = takeCup->next;
        take[1] = takeCup->getNum();
        takeCup = takeCup->next;
        take[2] = takeCup->getNum();

        int destinationCupNum = currentCup->getNum() - 1;
        if (destinationCupNum == 0) {
            destinationCupNum = _highestNumCup;
        }
        while (std::find(take.begin(), take.end(), destinationCupNum) != take.end()) {
            destinationCupNum -= 1;
            if (destinationCupNum == 0) {
                destinationCupNum = _highestNumCup;
            }
        }

        int destinationCupIndex = _lookupTable[destinationCupNum];
        Cup * newCurrentCup = currentCup->next->next->next->next;
        takeCup->next =  _cups[destinationCupIndex].next;
        _cups[destinationCupIndex].next = currentCup->next;
        currentCup->next = newCurrentCup;
        currentCup = currentCup->next;
    }
}

std::string CupGame::getResultAfterRounds(int rounds) {
    playRounds(rounds);

    std::string result;
    Cup * currentCup = &_cups[_lookupTable[1]];
    for (int i = 1; i < _cups.size(); i++) {
        currentCup = currentCup->next;
        result += std::to_string(currentCup->getNum());
    }
    return result;
}

std::vector<Cup*> CupGame::getStarCups(int rounds) {
    playRounds(rounds);
    return std::vector<Cup*>{_cups[_lookupTable[1]].next, _cups[_lookupTable[1]].next->next};
}
