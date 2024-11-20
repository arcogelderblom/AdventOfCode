#pragma once

#include <vector>
#include <string>

#include "Player.hpp"

class RecursiveCombatGame {
private:
    int recurseAmount = 0;
    std::vector<Player> _players;
    int getWinner(std::vector<int> & cards);
    void playRound();
    int play();
public:
    RecursiveCombatGame(std::vector<std::string> players);
    int getWinningPlayerScore();
};