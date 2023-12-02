#include <iostream>
#include <map>
#include <chrono>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::vector<std::string> getAutocompletedLines(std::vector<std::string> navigationSubsystem)
{
    std::vector<std::string> autocompletedLines;
    std::map<char, char> matchingCharPairs;
    matchingCharPairs['('] = ')';
    matchingCharPairs['['] = ']';
    matchingCharPairs['{'] = '}';
    matchingCharPairs['<'] = '>';
    for (std::string line : navigationSubsystem)
    {
        bool autocompleteLine = true;
        std::vector<char> expectedEnding;
        for (char character : line)
        {
            if (matchingCharPairs.find(character) != matchingCharPairs.end())
            {
                expectedEnding.push_back(matchingCharPairs[character]);
            }
            else 
            {
                if (expectedEnding.back() == character) 
                {
                    expectedEnding.erase(expectedEnding.end() - 1);
                }
                else 
                {
                    autocompleteLine = false;
                    break;
                }
            }
        }
        if (autocompleteLine)
        {
            autocompletedLines.push_back(std::string(expectedEnding.rbegin(), expectedEnding.rend()));
        }
    }
    return autocompletedLines;
}

std::vector<char> getIllegalChars(std::vector<std::string> navigationSubsystem)
{
    std::vector<char> illegalChars;
    std::map<char, char> matchingCharPairs;
    matchingCharPairs['('] = ')';
    matchingCharPairs['['] = ']';
    matchingCharPairs['{'] = '}';
    matchingCharPairs['<'] = '>';
    for (std::string line : navigationSubsystem)
    {
        std::vector<char> expectedEnding;
        for (char character : line)
        {
            if (matchingCharPairs.find(character) != matchingCharPairs.end())
            {
                expectedEnding.push_back(matchingCharPairs[character]);
            }
            else 
            {
                if (expectedEnding.back() == character) 
                {
                    expectedEnding.erase(expectedEnding.end() - 1);
                }
                else 
                {
                    illegalChars.push_back(character);
                    break;
                }
            }
        }
    }
    return illegalChars;
}

unsigned long getTotalSyntaxErrorScore(std::vector<std::string> navigationSubsystem)
{
    std::vector<char> illegalChars = getIllegalChars(navigationSubsystem);
    
    unsigned long result = 0;
    result += std::count(illegalChars.begin(), illegalChars.end(), ')') * 3;
    result += std::count(illegalChars.begin(), illegalChars.end(), ']') * 57;
    result += std::count(illegalChars.begin(), illegalChars.end(), '}') * 1197;
    result += std::count(illegalChars.begin(), illegalChars.end(), '>') * 25137;
    return result;
}

unsigned long getMiddleAutocompleteScore(std::vector<std::string> navigationSubsystem)
{
    std::vector<std::string> autocompletedLines = getAutocompletedLines(navigationSubsystem);
    std::vector<unsigned long> scores;
    std::map<char, int> charAndScore;
    charAndScore[')'] = 1;
    charAndScore[']'] = 2; 
    charAndScore['}'] = 3;
    charAndScore['>'] = 4; 

    for (std::string autocompletedLine : autocompletedLines)
    {
        unsigned long long score = 0;
        for (char c : autocompletedLine)
        {
            score = score * 5;
            score += charAndScore[c];
        }
        
        scores.push_back(score);
    }

    std::sort(scores.begin(), scores.end());
    return scores.at((scores.size() - 1) / 2);
}

int main(void)
{
    std::vector<std::string> testNavigationSubsystem = StringParser::toVector("[({(<(())[]>[[{[]{<()<>>\n[(()[<>])]({[<{<<[]>>(\n{([(<{}[<>[]}>{[]{[(<()>\n(((({<>}<{<{<>}{[]{[]{}\n[[<[([]))<([[{}[[()]]]\n[{[{({}]{}}([{[{{{}}([]\n{<[[]]>}<{[{[{[]{()[[[]\n[<(<(<(<{}))><([]([]()\n<{([([[(<>()){}]>(<<{{\n<{([{{}}[<[[[<>{}]]]>[]]", "\n");
    assert(getTotalSyntaxErrorScore(testNavigationSubsystem) == 26397);
    
    FileHandler fileHandler("input-files/2021/day10.txt");
    std::vector<std::string> navigationSubsystem = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 1: " << std::flush << getTotalSyntaxErrorScore(navigationSubsystem) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getMiddleAutocompleteScore(testNavigationSubsystem) == 288957);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 2: " << std::flush << getMiddleAutocompleteScore(navigationSubsystem) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
