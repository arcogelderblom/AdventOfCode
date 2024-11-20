#include "RecursiveCombatGame.hpp"

RecursiveCombatGame::RecursiveCombatGame(std::vector<std::string> players) {
    for (const std::string & player : players) {
        _players.emplace_back(player);
    }
}

int RecursiveCombatGame::getWinningPlayerScore() {
    int winningPlayer = play();
    std::vector<int> cards = _players[winningPlayer].getCards();
    int result = 0;
    for (int multiplicationNum = 1; multiplicationNum <= cards.size(); multiplicationNum++) {
        result += cards[cards.size() - multiplicationNum] * multiplicationNum;
    }
    return result;
}

int RecursiveCombatGame::getWinner(std::vector<int> & cards) {
    int cardPlayer1 = _players[0].getFirstCard();
    int cardPlayer2 = _players[1].getFirstCard();
    cards = std::vector<int>{cardPlayer1, cardPlayer2};

    if (cardPlayer1 <= _players[0].getCards().size() && cardPlayer2 <= _players[1].getCards().size()) {
        std::vector<Player> currentSet = _players;
        _players[0].shrinkDeck(cardPlayer1);
        _players[1].shrinkDeck(cardPlayer2);
        recurseAmount++;
        int winningPlayer = play();

        _players = currentSet;
        return winningPlayer;
    }

    if (cardPlayer1 > cardPlayer2) {
        return 0;
    }
    return 1;
}

void RecursiveCombatGame::playRound() {
    std::vector<int> playedCards;
    int winningPlayer = getWinner(playedCards);
    if (winningPlayer == 1) {
        playedCards = std::vector<int>{playedCards[1], playedCards[0]};
    }
    _players[winningPlayer].addToCards(playedCards);
}

int RecursiveCombatGame::play() {
    bool gameDone = false;
    std::vector< std::vector<Player> > previousRounds;
    while (!gameDone) {
        for (std::vector<Player> previousRound : previousRounds) {
            if (previousRound == _players) {
                return 0;
            }
        }
        previousRounds.push_back(_players);

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

    for (int player = 0; player < _players.size(); player++) {
        std::vector<int> cards = _players[player].getCards();
        if (!cards.empty()) {
            return player;
        }
    }
    return -1;
}
