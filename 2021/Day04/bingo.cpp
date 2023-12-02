#include "bingo.hpp"
#include <algorithm>

Bingo::Bingo(std::vector<std::string> bingoCards)
{
    for (std::string bingoCard : bingoCards) {
        _bingoCards.push_back(BingoCard(bingoCard));
    }
}

int Bingo::play(std::vector<int> drawnNumbers, bool playUntilLastOneWins)
{
    for (int drawnNumber : drawnNumbers)
    {
        std::vector<BingoCard> cardsToRemove;
        for (BingoCard& bingoCard : _bingoCards)
        {
            bingoCard.crossNumber(drawnNumber);

            if (bingoCard.hasBingo()) 
            {
                if (!playUntilLastOneWins || (playUntilLastOneWins && _bingoCards.size() == 1))
                {
                    return bingoCard.getSumUnmarkedNumbers() * drawnNumber;
                }
                else if (playUntilLastOneWins && _bingoCards.size() != 1)
                {
                    cardsToRemove.push_back(bingoCard);
                }
            }
        }

        for (BingoCard cardToRemove : cardsToRemove)
        {
            
            _bingoCards.erase(std::find(_bingoCards.begin(), _bingoCards.end(), cardToRemove));
        }
    }
    return -1;
}
