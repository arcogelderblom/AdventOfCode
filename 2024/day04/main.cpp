#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

// LU UU RU
// LL .. RR
// LD DD RD
enum Direction
{
    LU,
    UU,
    RU,
    LL,
    RR,
    LD,
    DD,
    RD
};

// directions are represented as x,y coordinates
std::map<Direction, std::pair<int,int>> createDirectionsMap()
{
    std::map<Direction, std::pair<int,int>> directions;
    directions[LU] = std::make_pair(-1, -1);
    directions[UU] = std::make_pair(0, -1);
    directions[RU] = std::make_pair(1, -1);
    directions[LL] = std::make_pair(-1, 0);
    directions[RR] = std::make_pair(1, 0);
    directions[LD] = std::make_pair(-1, 1);
    directions[DD] = std::make_pair(0, 1);
    directions[RD] = std::make_pair(1, 1);
    return directions;
}

bool isInBounds(const std::pair<int,int> & c, const std::vector<std::string>& wordSearch)
{
    return c.first < wordSearch[c.second].size() && 
            c.first >= 0 &&
            c.second < wordSearch.size() &&
            c.second >= 0;
}

// returns true if full word is found
bool searchWordInDirection(const std::vector<std::string>& wordSearch, std::pair<int,int> c, const std::string & word, std::pair<int, int> direction)
{
    for (int i = 1; i < word.size(); i++)
    {
        c.first += direction.first;
        c.second += direction.second;
        if (!isInBounds(c, wordSearch))
        {
            return false;
        }

        if (wordSearch[c.second][c.first] != word[i])
        {
            return false;
        }
    }
    return true;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::string word = "XMAS";
    std::map<Direction, std::pair<int,int>> directions = createDirectionsMap();
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            if (input[y][x] == word[0])
            {
                for (int d = LU; d <= RD; d++)
                {
                    if (searchWordInDirection(input, std::make_pair(x, y), word, directions[static_cast<Direction>(d)]))
                    {
                        result++;
                    }
                }
            }
        }
    }
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    
    std::map<Direction, std::pair<int,int>> directions = createDirectionsMap();
    for (int y = 1; y < input.size() - 1; y++)
    {
        for (int x = 1; x < input[y].size() - 1; x++)
        {
            if (input[y][x] == 'A')
            {
                std::string first, second;
                first += input[y + directions[LU].second][x + directions[LU].first];
                first += input[y][x];
                first += input[y + directions[RD].second][x + directions[RD].first];

                second += input[y + directions[RU].second][x + directions[RU].first];
                second += input[y][x];
                second += input[y + directions[LD].second][x + directions[LD].first];
                
                if ((first == "MAS" || first == "SAM") && (second == "MAS" || second == "SAM"))
                {
                    result++;
                }
            }
        }
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day04_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 18);
    
    FileHandler fileHandler("input-files/2024/day04.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 9);
    
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}