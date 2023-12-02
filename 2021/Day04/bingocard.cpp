#include "bingocard.hpp"
#include "StringParser.hpp"
#include <iostream>
#include <algorithm>

BingoCard::BingoCard(std::string card)
{
    std::vector<std::string> card_vector = StringParser::toVector(card, "\n");
    std::vector< std::vector<int> > currentCard;
    for (std::string item : card_vector)
    {
        currentCard.push_back(StringParser::toIntVector(item, " "));
    }
    
    _card = currentCard;
    std::vector<bool> row(_card[0].size(), false);
    std::vector<std::vector<bool> > crossedElements(_card.size(), row);
    _crossedElements = crossedElements;
}

void BingoCard::crossNumber(int num)
{
    bool crossedNumberOff = false;
    for (int i = 0; i < _card.size(); i++)
    {
        for (int j = 0; j < _card[0].size(); j++)
        {
            if (_card[i][j] == num) {
                _crossedElements[i][j] = true;
                crossedNumberOff = true;
            }
        }
    }
    _isChangedSinceLastNum = crossedNumberOff;
}

bool BingoCard::hasBingo()
{
    if (_isChangedSinceLastNum)
    {
        for (std::vector<bool> row : _crossedElements) 
        {
            if (std::find(row.begin(), row.end(), false) == row.end()) // no more uncrossed (false) elements
            {
                return true;
            }
        }
        for (int i = 0; i < _crossedElements.size(); i++) 
        {
            std::vector<bool> column;
            for (int j = 0; j < _crossedElements[0].size(); j++)
            {
                column.push_back(_crossedElements[j][i]);
            }
            if (std::find(column.begin(), column.end(), false) == column.end()) // no more uncrossed (false) elements
            {
                return true;
            }
        }
    }
    return false;
}

int BingoCard::getSumUnmarkedNumbers()
{
    int sum = 0;
    for (int i = 0; i < _card.size(); i++)
    {
        for (int j = 0; j < _card[0].size(); j++)
        {
            if (!_crossedElements[i][j])
            {
                sum += _card[i][j];
            }
        }
    } 
    return sum;
}

void BingoCard::printCard()
{
    for (int i = 0; i < _card.size(); i++)
    {
        for (int j = 0; j < _card[0].size(); j++)
        {
            if (_crossedElements[i][j])
            {
                std::cout  << "-"<< _card[i][j] << "- ";
            }
            else 
            {
                std::cout << _card[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}