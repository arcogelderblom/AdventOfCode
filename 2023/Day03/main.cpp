#include <iostream>
#include <cassert>
#include <chrono>

#include <set>
#include <map>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool isPartNr(const std::vector<std::string> & input, const int & x, const int & y, const std::set<std::pair<int,int>> & directions)
{
    for (const std::pair<int,int> & direction : directions)
    {
        if ((y+direction.second >= 0 && y+direction.second < input.size()) && (x+direction.first >= 0 && x+direction.first < input[y].size())) 
        {
            char c = input[y+direction.second][x+direction.first];
            if (!isdigit(c) && c != '.')
            {
                return true;
            }
        }
    }
    return false;
}

bool isGear(const std::vector<std::string> & input, const int & x, const int & y, const std::set<std::pair<int,int>> & directions, int & gearX, int & gearY)
{
    for (const std::pair<int,int> & direction : directions)
    {
        if ((y+direction.second >= 0 && y+direction.second < input.size()) && (x+direction.first >= 0 && x+direction.first < input[y].size())) 
        {
            char c = input[y+direction.second][x+direction.first];
            if (c == '*')
            {
                gearX = x+direction.first;
                gearY = y+direction.second;
                return true;
            }
        }
    }
    return false;
}

long part1(const std::vector<std::string> & input) 
{
    std::set<std::pair<int,int>> directionsFirstDigit { std::make_pair(-1,-1),
                                                        std::make_pair(-1, 0),
                                                        std::make_pair(-1, 1),
                                                        std::make_pair( 0,-1),
                                                        std::make_pair( 0, 1)};

    std::set<std::pair<int,int>> directionsMiddleDigit { std::make_pair( 0,-1),
                                                         std::make_pair( 0, 1)};

    std::set<std::pair<int,int>> directionsLastDigit { std::make_pair( 0,-1),
                                                       std::make_pair( 0, 1),
                                                       std::make_pair( 1,-1),
                                                       std::make_pair( 1, 0),
                                                       std::make_pair( 1, 1) };
                                                       
    std::set<std::pair<int,int>> directionsSingleDigit { std::make_pair(-1,-1),
                                                         std::make_pair(-1, 0),
                                                         std::make_pair(-1, 1),
                                                         std::make_pair( 0,-1),
                                                         std::make_pair( 0, 1),
                                                         std::make_pair( 1, -1),
                                                         std::make_pair( 1, 0),
                                                         std::make_pair( 1, 1)};

    long result = 0;
    // find part numbers
    for (int y = 0; y < input.size(); y++)
    {
        std::string currentPartNrStr = "";
        bool currentIsPartNr = false;
        for (int x = 0; x < input[y].size(); x++)
        {
            if (isdigit(input[y][x]))
            {
                if (!currentIsPartNr)
                {
                    if (currentPartNrStr.empty())
                    {
                        if (x+1 < input[y].size() && !isdigit(input[y][x+1]))
                        {
                            currentIsPartNr = isPartNr(input, x, y, directionsSingleDigit);
                        }
                        else 
                        {
                            currentIsPartNr = isPartNr(input, x, y, directionsFirstDigit);
                        }
                    }
                    else 
                    {
                        if (x+1 < input[y].size() && !isdigit(input[y][x+1]))
                        {
                            currentIsPartNr = isPartNr(input, x, y, directionsLastDigit);
                        }
                        else 
                        {
                            currentIsPartNr = isPartNr(input, x, y, directionsMiddleDigit);
                        }
                    }
                }
                currentPartNrStr += input[y][x];
            }
            else if (!currentPartNrStr.empty())
            {
                if (currentIsPartNr)
                {
                    result += std::stoi(currentPartNrStr);
                }
                
                currentPartNrStr = "";
                currentIsPartNr = false;
            }
        }

        if (!currentPartNrStr.empty())
        {
            if (currentIsPartNr)
            {
                result += std::stoi(currentPartNrStr);
            }
            
            currentPartNrStr = "";
            currentIsPartNr = false;
        }
    }
    
    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    std::set<std::pair<int,int>> directionsFirstDigit { std::make_pair(-1,-1),
                                                        std::make_pair(-1, 0),
                                                        std::make_pair(-1, 1),
                                                        std::make_pair( 0,-1),
                                                        std::make_pair( 0, 1)};

    std::set<std::pair<int,int>> directionsMiddleDigit { std::make_pair( 0,-1),
                                                         std::make_pair( 0, 1)};

    std::set<std::pair<int,int>> directionsLastDigit { std::make_pair( 0,-1),
                                                       std::make_pair( 0, 1),
                                                       std::make_pair( 1,-1),
                                                       std::make_pair( 1, 0),
                                                       std::make_pair( 1, 1) };
                                                       
    std::set<std::pair<int,int>> directionsSingleDigit { std::make_pair(-1,-1),
                                                         std::make_pair(-1, 0),
                                                         std::make_pair(-1, 1),
                                                         std::make_pair( 0,-1),
                                                         std::make_pair( 0, 1),
                                                         std::make_pair( 1, -1),
                                                         std::make_pair( 1, 0),
                                                         std::make_pair( 1, 1)};

    long long result = 0;

    std::map<std::pair<int, int>, std::vector<int>> gearLocationAndParts;
    for (int y = 0; y < input.size(); y++)
    {
        std::string currentPartNrStr = "";
        bool currentIsGear = false;
        int gearX, gearY = 0;
        for (int x = 0; x < input[y].size(); x++)
        {
            if (isdigit(input[y][x]))
            {
                if (!currentIsGear)
                {
                    if (currentPartNrStr.empty())
                    {
                        if (x+1 < input[y].size() && !isdigit(input[y][x+1]))
                        {
                            currentIsGear = isGear(input, x, y, directionsSingleDigit, gearX, gearY);
                        }
                        else 
                        {
                            currentIsGear = isGear(input, x, y, directionsFirstDigit, gearX, gearY);
                        }
                    }
                    else 
                    {
                        if (x+1 < input[y].size() && !isdigit(input[y][x+1]))
                        {
                            currentIsGear = isGear(input, x, y, directionsLastDigit, gearX, gearY);
                        }
                        else 
                        {
                            currentIsGear = isGear(input, x, y, directionsMiddleDigit, gearX, gearY);
                        }
                    }
                }
                currentPartNrStr += input[y][x];
            }
            else if (!currentPartNrStr.empty())
            {
                if (currentIsGear)
                {
                    gearLocationAndParts[std::make_pair(gearX, gearY)].push_back(std::stoi(currentPartNrStr));
                }
                
                currentPartNrStr = "";
                currentIsGear = false;
                gearX = 0;
                gearY = 0;
            }
        }

        if (!currentPartNrStr.empty())
        {
            if (currentIsGear)
            {
                gearLocationAndParts[std::make_pair(gearX, gearY)].push_back(std::stoi(currentPartNrStr));
            }
            
            currentPartNrStr = "";
            currentIsGear = false;
            gearX = 0;
            gearY = 0;
        }
    }
    
    for (auto elem : gearLocationAndParts)
    {
        if (elem.second.size() == 2)
        {
            result += (elem.second[0] * elem.second[1]);
        }
    }

    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day03_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 4361);

    FileHandler fileHandler("input-files/2023/day03.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 467835);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}