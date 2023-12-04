#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <algorithm>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long part1(const std::vector<std::string> & input) 
{
    int result = 0;
    for (const std::string & line : input)
    {
        std::vector<std::string> parsedLine = StringParser::toVector(line.substr(line.find(": ") + 2), " | ");
        std::vector<int> winningNumbers = StringParser::toIntVector(parsedLine[0], " ");
        std::vector<int> ownNumbers = StringParser::toIntVector(parsedLine[1], " ");
        int currentScore = 0;
        for (const int & num : ownNumbers)
        {
            if (std::find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end())
            {
                if (currentScore == 0)
                {
                    currentScore = 1;
                }
                else 
                {
                    currentScore *= 2;
                }
            }
        }
        result += currentScore;
    }
    return result;
}

long part2(const std::vector<std::string> & input) 
{
    int result = 0;
    std::map<int, int> copiesPerCard;
    copiesPerCard[1] = 0;
    for (int i = 0; i < input.size(); i++)
    {
        int currentCardNr = i + 1;
        std::vector<std::string> parsedLine = StringParser::toVector(input[i].substr(input[i].find(": ") + 2), " | ");
        std::vector<int> winningNumbers = StringParser::toIntVector(parsedLine[0], " ");
        std::vector<int> ownNumbers = StringParser::toIntVector(parsedLine[1], " ");
        int newCards = 0;
        for (const int & num : ownNumbers)
        {
            if (newCards == input.size() - (i + 1))
            {
                break;
            }
            if (std::find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end())
            {
                newCards++;
            }
        }
        for (int cardCopyNr = currentCardNr + newCards; cardCopyNr > currentCardNr; cardCopyNr--)
        {
            copiesPerCard[cardCopyNr] += (1 * (1 + copiesPerCard[currentCardNr]));
        }
    }

    for (const std::pair<int, int> & elem : copiesPerCard)
    {
        result += elem.second;
    }
    result += input.size(); // add starting cards as well
    
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day04_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 13);

    FileHandler fileHandler("input-files/2023/day04.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 30);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}