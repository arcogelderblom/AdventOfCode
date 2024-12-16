#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include <set>

#include "StringParser.hpp"
#include "FileHandler.hpp"

std::vector<std::string> findNiceStringsFirstRules(std::vector<std::string> allStrings)
{
    std::vector<std::string> niceStrings;
    for (const std::string cur_string : allStrings)
    {
        int amountOfVowels = 0;
        bool doubleFound = false;
        char lastChar = '\0';
        bool naughtySubstringFound = false;
        for (char c : cur_string)
        {
            if (lastChar == 'a' && c == 'b' || 
                lastChar == 'c' && c == 'd'  || 
                lastChar == 'p' && c == 'q'  || 
                lastChar == 'x' && c == 'y' )
            {
                naughtySubstringFound = true;
                break;
            }
            else if (lastChar == c)
            {
                doubleFound = true;
            }
            
            if (std::string("aeiou").find(c) != std::string::npos)
            {
                amountOfVowels++;
            }
            lastChar = c;
        }

        if (doubleFound && ! naughtySubstringFound && amountOfVowels >= 3)
        {
            niceStrings.push_back(cur_string);
        }
    }
    return niceStrings;
}


std::vector<std::string> findNiceStringsSecondRules(std::vector<std::string> allStrings)
{
    std::vector<std::string> niceStrings;
    for (const std::string cur_string : allStrings)
    {
        bool doublePair = false;
        bool repetitionWithLetterInBetween = false;
        for (int i = 0; i < cur_string.size() - 1; i++)
        {
            if (!repetitionWithLetterInBetween)
            {
                if (i < cur_string.size() - 2)
                {
                    if (cur_string[i] == cur_string[i+2])
                    {
                        repetitionWithLetterInBetween = true;
                    }
                }
            }

            if (!doublePair)
            {
                int count = 0;
                for (int j = 0; j < cur_string.size() - 1; j++)
                {
                    if (cur_string[i] == cur_string[j] && cur_string[i+1] == cur_string[j+1])
                    {
                        count++;
                        j += 1;
                    }
                    if (count == 2)
                    {
                        doublePair = true;
                    }
                }
            }
        }
        if (doublePair && repetitionWithLetterInBetween)
        {
            niceStrings.push_back(cur_string);
        }
    }
    return niceStrings;
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day05.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 1: " << std::flush << findNiceStringsFirstRules(input).size() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
   std::cout << "Day 5, puzzle 2: " << std::flush << findNiceStringsSecondRules(input).size() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}