#include "CombatGame.hpp"

#include <map>

CombatGame::CombatGame(std::vector<std::string> players) {
    for (const std::string & player : players) {
        _players.emplace_back(player);
    }
}

int CombatGame::getWinningPlayerScore() {
    play();
    for (Player player : _players) {
        std::vector<int> cards = player.getCards();
        if (!cards.empty()) {
            int result = 0;
            for (int multiplicationNum = 1; multiplicationNum <= cards.size(); multiplicationNum++) {
                result += cards[cards.size() - multiplicationNum] * multiplicationNum;
            }
            return result;
        }
    }
    return 0;
}

void CombatGame::playRound() {
    int cardPlayer1 = _players[0].getFirstCard();
    int cardPlayer2 = _players[1].getFirstCard();

    if (cardPlayer1 > cardPlayer2) {
        std::vector<int> winningCards = {cardPlayer1, cardPlayer2};
        _players[0].addToCards(winningCards);
    }
    else {
        std::vector<int> winningCards = {cardPlayer2, cardPlayer1};
        _players[1].addToCards(winningCards);
    }
}

void CombatGame::play() {
    bool gameDone = false;
    while (!gameDone) {
        playRound();

        int playersWithCards = 0;
        for (Player player : _players) {
            if (!player.getCards().empty()) {
                playersWithCards++;
            }
        }
        if (playersWithCards <= 1) {
            gameDone = true;
        }
    }
}
