#pragma once

#include <vector>
#include <string>

#include "Player.hpp"

class CombatGame {
private:
    std::vector<Player> _players;
    void playRound();
    void play();
public:
    CombatGame(std::vector<std::string> players);
    int getWinningPlayerScore();
};