#include "Player.hpp"

Player::Player(std::string playerString) {
    // skip first line
    playerString = playerString.substr(playerString.find('\n') + 1);
    while (playerString.find('\n') != std::string::npos) {
        _cards.push_back(std::stoi(playerString.substr(0, playerString.find('\n'))));
        playerString = playerString.substr(playerString.find('\n') + 1);
    }
    _cards.push_back(std::stoi(playerString));
}

std::vector<int> Player::getCards() {
    return _cards;
}

int Player::getFirstCard() {
    int firstCard = _cards.front();
    _cards.erase(_cards.begin());
    return firstCard;
}

void Player::addToCards(std::vector<int> winningCards) {
    for (int card : winningCards) {
        _cards.push_back(card);
    }
}

void Player::shrinkDeck(int size) {
    _cards.resize(size);
}