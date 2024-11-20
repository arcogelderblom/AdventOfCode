#pragma once

#include <vector>
#include <string>

class Player {
private:
    std::vector<int> _cards;
public:
    Player(std::string playerString);
    std::vector<int> getCards();
    int getFirstCard();
    void addToCards(std::vector<int> winningCards);
    void shrinkDeck(int size);

    friend bool operator==(const Player& lhs, const Player& rhs) {
        return lhs._cards == rhs._cards;
    }

    friend bool operator<(const Player& lhs, const Player& rhs) {
        return lhs._cards.size() <= rhs._cards.size();
    }
};