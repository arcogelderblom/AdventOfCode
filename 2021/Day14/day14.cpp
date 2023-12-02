#include <iostream>
#include <chrono>
#include <map>
#include <set>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::map<std::string, unsigned long> executeStepPolymerTemplate(std::string startPolymerTemplate, std::map<std::string, std::string> pairInsertionRules, int amountOfSteps)
{
    std::map<std::string, unsigned long> elementsCount;
    for (int i = 0; i < startPolymerTemplate.size(); i++)
    {
        elementsCount[std::string(1, startPolymerTemplate[i])] += 1;
    }

    std::map<std::string, unsigned long> pairAndAmount;
    for (int i = 0; i < startPolymerTemplate.size() - 1; i++)
    {
        std::string current = startPolymerTemplate.substr(i, 2);
        pairAndAmount[current] += 1;
    }

    for (int step = 0; step < amountOfSteps; step++)
    {
        std::map<std::string, unsigned long> pairAndAmountCopy = pairAndAmount;
        for (std::pair<std::string, unsigned long> currentPairAndAmount : pairAndAmountCopy)
        {
            pairAndAmount[std::string(currentPairAndAmount.first[0] + pairInsertionRules[currentPairAndAmount.first])] += pairAndAmountCopy[currentPairAndAmount.first];
            pairAndAmount[std::string(pairInsertionRules[currentPairAndAmount.first] + currentPairAndAmount.first[1])] += pairAndAmountCopy[currentPairAndAmount.first];
            elementsCount[pairInsertionRules[currentPairAndAmount.first]] += pairAndAmountCopy[currentPairAndAmount.first];
            pairAndAmount[currentPairAndAmount.first] -= pairAndAmountCopy[currentPairAndAmount.first];
        }

        for (auto it = pairAndAmount.begin(); it != pairAndAmount.end();)
        {   
            (it->second == 0) ? pairAndAmount.erase(it++) : (++it);
        }
    }
    return elementsCount;
}

unsigned long getResult(std::string startPolymerTemplate, std::vector<std::string> pairInsertionRules, int amountOfSteps)
{
    std::set<char> possibleElements;
    std::map<std::string, std::string> pairInsertionRulesMap;
    for (std::string pairInsertionRule : pairInsertionRules)
    {
        std::vector<std::string> pairAndInsertionRule = StringParser::toVector(pairInsertionRule, " -> ");
        pairInsertionRulesMap[pairAndInsertionRule[0]] = pairAndInsertionRule[1];
        possibleElements.insert(pairAndInsertionRule[1][0]);
    }
    
    std::map<std::string, unsigned long> elementsCount = executeStepPolymerTemplate(startPolymerTemplate, pairInsertionRulesMap, amountOfSteps);
    unsigned long mostCommonElementCount = 0, leastCommonElementCount = std::numeric_limits<unsigned long>::max();;
    for (std::pair<std::string, unsigned long> elementAndCount : elementsCount)
    {
        if (elementAndCount.second < leastCommonElementCount)
        {
            leastCommonElementCount = elementAndCount.second;
        }
        if (elementAndCount.second > mostCommonElementCount)
        {
            mostCommonElementCount = elementAndCount.second;
        }
    }

    return mostCommonElementCount - leastCommonElementCount;
}

int main(void)
{
    std::string testInput = "NNCB\n\nCH -> B\nHH -> N\nCB -> H\nNH -> C\nHB -> C\nHC -> B\nHN -> C\nNN -> C\nBH -> H\nNC -> B\nNB -> B\nBN -> B\nBB -> N\nBC -> B\nCC -> N\nCN -> C";
    std::string testPolymerTemplate = StringParser::toVector(testInput, "\n\n")[0];
    std::vector<std::string> testPairInsertionRules = StringParser::toVector(StringParser::toVector(testInput, "\n\n")[1], "\n");
    assert(getResult(testPolymerTemplate, testPairInsertionRules, 10) == 1588);
    
    FileHandler fileHandler("input-files/2021/day14.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
    std::string polymerTemplate = input[0];
    std::vector<std::string> pairInsertionRules = StringParser::toVector(input[1], "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 1: " << std::flush << getResult(polymerTemplate, pairInsertionRules, 10) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getResult(testPolymerTemplate, testPairInsertionRules, 40) == 2188189693529);
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 14, puzzle 2: " << std::flush << getResult(polymerTemplate, pairInsertionRules, 40) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
