#pragma once

#include <map>
#include <vector>
#include <string>

#include "Cup.hpp"

class CupGame {
private:
    std::vector<Cup> _cups;
    std::map<int, int> _lookupTable;
    int _highestNumCup = 0;
    void playRounds(int rounds);
public:
    CupGame(std::string cups, int totalAmountOfCups);
    std::string getResultAfterRounds(int rounds);
    std::vector<Cup*> getStarCups(int rounds);
};