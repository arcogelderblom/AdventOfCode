#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <algorithm>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

void outputVector(const std::vector<std::string> & src)
{
    std::cout << "Vector contents:" << std::endl;
    for (const auto & line : src)
    {
        std::cout << "\t" << line << std::endl;
    }
    std::cout << std::endl;
}

void rank(std::vector<std::string> & src, bool part2 = false)
{
    // order: A K Q J T 9 8 7 6 5 4 3 2
    std::map<char, int> rankedCards = { {'A', 12}, {'K', 11}, {'Q', 10}, {'J', 9}, {'T', 8}, {'9', 7}, {'8', 6}, {'7', 5}, {'6', 4}, {'5', 3}, {'4', 2}, {'3', 1}, {'2', 0} };
    if (part2)
    {
        rankedCards['J'] = -1; // Joker is lowest ranked card
    }
    
    for (auto it = src.begin(); it != src.end(); ++it)
    {
        for (auto it2 = src.begin(); it2 != it; it2++)
        {
            for (int i = 0; i < 5; i++)
            {
                if (rankedCards[(*it)[i]] > rankedCards[(*it2)[i]])
                {
                    std::iter_swap(it, it2);
                    break;
                }
                else if (rankedCards[(*it)[i]] < rankedCards[(*it2)[i]])
                {
                    break;
                }
            }
        }
    }
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::map<std::string, int> handsAndBids;
    std::vector<std::string> fiveOfAKinds;
    std::vector<std::string> fourOfAKinds;
    std::vector<std::string> fullHouses;
    std::vector<std::string> threeOfAKinds;
    std::vector<std::string> twoPairs;
    std::vector<std::string> onePairs;
    std::vector<std::string> highCards;

    for (const std::string & line : input)
    {
        std::vector<std::string> parsed = StringParser::toVector(line, " ");
        const std::string currentCard = parsed[0];
        handsAndBids[currentCard] = std::stoi(parsed[1]);
        std::map<char, int> countPerCard;
        for (const char & card : currentCard)
        {
            countPerCard[card]++;
        }

        switch (countPerCard.size())
        {
            case 5:
            {
                highCards.push_back(currentCard);
                break;
            }
            case 4:
            {
                onePairs.push_back(currentCard);
                break;
            }
            case 3:
            {
                for (const std::pair<char, int> & cardAndCount : countPerCard)
                {
                    if (cardAndCount.second == 3)
                    {
                        threeOfAKinds.push_back(currentCard);
                        break;
                    }
                    else if (cardAndCount.second == 2)
                    {
                        twoPairs.push_back(currentCard);
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                for (const std::pair<char, int> & cardAndCount : countPerCard)
                {
                    if (cardAndCount.second == 4)
                    {
                        fourOfAKinds.push_back(currentCard);
                        break;
                    }
                    else if (cardAndCount.second == 3)
                    {
                        fullHouses.push_back(currentCard);
                        break;
                    }
                }
                break;
            }
            case 1:
            {
                fiveOfAKinds.push_back(currentCard);
                break;
            }
        }
    }
 
    rank(fiveOfAKinds);
    rank(fourOfAKinds);
    rank(fullHouses);
    rank(threeOfAKinds);
    rank(twoPairs);
    rank(onePairs);
    rank(highCards);

    std::vector<std::string> completeRankedList;
    completeRankedList.insert(completeRankedList.end(), fiveOfAKinds.begin(), fiveOfAKinds.end());
    completeRankedList.insert(completeRankedList.end(), fourOfAKinds.begin(), fourOfAKinds.end());
    completeRankedList.insert(completeRankedList.end(), fullHouses.begin(), fullHouses.end());
    completeRankedList.insert(completeRankedList.end(), threeOfAKinds.begin(), threeOfAKinds.end());
    completeRankedList.insert(completeRankedList.end(), twoPairs.begin(), twoPairs.end());
    completeRankedList.insert(completeRankedList.end(), onePairs.begin(), onePairs.end());
    completeRankedList.insert(completeRankedList.end(), highCards.begin(), highCards.end());

    for (int i = 0; i < completeRankedList.size(); i++)
    {
        result += ((completeRankedList.size() - i) * handsAndBids[completeRankedList[i]]);
    }

    return result;
}

unsigned long long part2(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;

    std::map<std::string, int> handsAndBids;
    std::vector<std::string> fiveOfAKinds;
    std::vector<std::string> fourOfAKinds;
    std::vector<std::string> fullHouses;
    std::vector<std::string> threeOfAKinds;
    std::vector<std::string> twoPairs;
    std::vector<std::string> onePairs;
    std::vector<std::string> highCards;

    for (const std::string & line : input)
    {
        std::vector<std::string> parsed = StringParser::toVector(line, " ");
        const std::string currentCard = parsed[0];
        handsAndBids[currentCard] = std::stoi(parsed[1]);
        std::map<char, int> countPerCard;
        for (const char & card : currentCard)
        {
            countPerCard[card]++;
        }

        if (countPerCard.size() == 5)
        {
            if (countPerCard['J'] == 1)
            {
                onePairs.push_back(currentCard);
            }
            else
            {
                highCards.push_back(currentCard);
            }
        }
        else if (countPerCard.size() == 4)
        {
            if (countPerCard['J'] == 1 || countPerCard['J'] == 2)
            {
                threeOfAKinds.push_back(currentCard);
            }
            else
            {
                onePairs.push_back(currentCard);
            }
        }
        else if (countPerCard.size() == 3)
        {
            for (const std::pair<char, int> & cardAndCount : countPerCard)
            {
                
                if (cardAndCount.second == 3)
                {
                    if (cardAndCount.first == 'J' || countPerCard['J'] == 1)
                    {
                        fourOfAKinds.push_back(currentCard);
                    }
                    else
                    {
                        threeOfAKinds.push_back(currentCard);
                    }
                    break;
                }
                else if (cardAndCount.second == 2)
                {
                    if (cardAndCount.first == 'J' || countPerCard['J'] == 2)
                    {
                        fourOfAKinds.push_back(currentCard);
                    }
                    else if (countPerCard['J'] == 1)
                    {
                        fullHouses.push_back(currentCard);
                    }
                    else
                    {
                        twoPairs.push_back(currentCard);
                    }
                    break;
                }
            }
        }
        else if (countPerCard.size() == 2)
        {
            for (const std::pair<char, int> & cardAndCount : countPerCard)
            {
                if (cardAndCount.second == 4)
                {
                    if (cardAndCount.first == 'J' || countPerCard['J'] == 1)
                    {
                        fiveOfAKinds.push_back(currentCard);
                    }
                    else
                    {
                        fourOfAKinds.push_back(currentCard);
                    }
                    break;
                }
                else if (cardAndCount.second == 3)
                {
                    if (cardAndCount.first == 'J' || countPerCard['J'] == 2)
                    {
                        fiveOfAKinds.push_back(currentCard);
                    }
                    else
                    {
                        fullHouses.push_back(currentCard);
                    }
                    break;
                }
            }
        }
        else if (countPerCard.size() == 1)
        {
            fiveOfAKinds.push_back(currentCard);
        }
    }

    rank(fiveOfAKinds, true);
    rank(fourOfAKinds, true);
    rank(fullHouses, true);
    rank(threeOfAKinds, true);
    rank(twoPairs, true);
    rank(onePairs, true);
    rank(highCards, true); 

    std::vector<std::string> completeRankedList;
    completeRankedList.insert(completeRankedList.end(), fiveOfAKinds.begin(), fiveOfAKinds.end());
    completeRankedList.insert(completeRankedList.end(), fourOfAKinds.begin(), fourOfAKinds.end());
    completeRankedList.insert(completeRankedList.end(), fullHouses.begin(), fullHouses.end());
    completeRankedList.insert(completeRankedList.end(), threeOfAKinds.begin(), threeOfAKinds.end());
    completeRankedList.insert(completeRankedList.end(), twoPairs.begin(), twoPairs.end());
    completeRankedList.insert(completeRankedList.end(), onePairs.begin(), onePairs.end());
    completeRankedList.insert(completeRankedList.end(), highCards.begin(), highCards.end());

    for (int i = 0; i < completeRankedList.size(); i++)
    {
        result += ((completeRankedList.size() - i) * handsAndBids[completeRankedList[i]]);
    }

    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day07_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 6440);

    FileHandler fileHandler("input-files/2023/day07.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 5905);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}