#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Direction getDirection(const char & c)
{
    if (c == '^')
    {
        return Direction::UP;
    }
    if (c == 'v')
    {
        return Direction::DOWN;
    }
    if (c == '<')
    {
        return Direction::LEFT;
    }
    if (c == '>')
    {
        return Direction::RIGHT;
    }
    throw std::exception();
}

std::pair<int, int> getRobotLocation(const std::vector<std::string> & map)
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == '@')
            {
                return std::make_pair(x, y);
            }
        }   
    }
    return std::make_pair(-1, -1);
}

int getGPSCoordinates(const std::vector<std::string> & map)
{
    int result = 0;
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if ((map[y][x] == 'O') || (map[y][x] == '['))
            {
                result += (100 * y) + x;
            }
        }   
    }
    return result;
}

std::vector<std::string> createMapPart2(const std::vector<std::string> & map)
{
    std::vector<std::string> newMap;
    for (const std::string & row : map)
    {
        std::string newRow;
        for (const char & c : row)
        {
            if (c == '#')
            {
                newRow += "##";
            }
            else if (c == 'O')
            {
                newRow += "[]";
            }
            else if (c == '.')
            {
                newRow += "..";
            }
            else if (c == '@')
            {
                newRow += "@.";
            }
        }
        newMap.push_back(newRow);
    }
    return newMap;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<std::string> map = StringParser::toVector(input[0], "\n");
    std::pair<int, int> robotLocation = getRobotLocation(map);

    std::string instructions = input[1];
    std::map<Direction, std::pair<int, int>> directions = { { Direction::UP, { 0, -1 } }, 
                                                            { Direction::DOWN, { 0, 1 } }, 
                                                            { Direction::LEFT, { -1, 0 } }, 
                                                            { Direction::RIGHT, { 1, 0 } } };

    for (const char & instruction : instructions)
    {
        if (instruction == '\n') { continue; }
        Direction d = getDirection(instruction);
        std::pair<int, int> newRobotLocation = std::make_pair(robotLocation.first + directions[d].first, robotLocation.second + directions[d].second);
        if (map[newRobotLocation.second][newRobotLocation.first] == '.')
        {
            map[robotLocation.second][robotLocation.first] = '.';
            map[newRobotLocation.second][newRobotLocation.first] = '@';
            robotLocation = newRobotLocation;
        }
        else
        {
            std::pair<int, int> newLocation = newRobotLocation;
            std::vector<std::pair<int, int>> boxesToMove;
            while (map[newLocation.second][newLocation.first] == 'O')
            {
                boxesToMove.push_back(newLocation);
                newLocation = std::make_pair(newLocation.first + directions[d].first, newLocation.second + directions[d].second);
            }

            if (map[newLocation.second][newLocation.first] == '.')
            {
                std::reverse(boxesToMove.begin(), boxesToMove.end());
                for (const std::pair<int, int> boxLocation : boxesToMove)
                {
                    map[boxLocation.second][boxLocation.first] = '.';
                    map[boxLocation.second + directions[d].second][boxLocation.first + directions[d].first] = 'O';
                }

                map[robotLocation.second][robotLocation.first] = '.';
                map[newRobotLocation.second][newRobotLocation.first] = '@';
                robotLocation = newRobotLocation;
            }
        }
    }

    result = getGPSCoordinates(map);
    
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<std::string> map = createMapPart2(StringParser::toVector(input[0], "\n"));
    std::pair<int, int> robotLocation = getRobotLocation(map);

    std::string instructions = input[1];
    std::map<Direction, std::pair<int, int>> directions = { { Direction::UP, { 0, -1 } }, 
                                                            { Direction::DOWN, { 0, 1 } }, 
                                                            { Direction::LEFT, { -1, 0 } }, 
                                                            { Direction::RIGHT, { 1, 0 } } };

    for (const char & instruction : instructions)
    {
        if (instruction == '\n') { continue; } // ignore newlines, just continue

        Direction d = getDirection(instruction);
        std::pair<int, int> newRobotLocation = std::make_pair(robotLocation.first + directions[d].first, robotLocation.second + directions[d].second);
        
        std::set<std::pair<int, int>> facesToCheck = { newRobotLocation };
        bool canMove = true;
        std::vector<std::pair<int, int>> boxesToMove;
        while (facesToCheck.size() > 0)
        {
            std::pair<int, int> current = *facesToCheck.begin();
            facesToCheck.erase(current);

            if (map[current.second][current.first] == '#')
            {
                canMove = false;
                break;
            }

            if (map[current.second][current.first] == '[' || map[current.second][current.first] == ']')
            {
                if (map[current.second][current.first] == ']')
                {
                    current.first -= 1;
                }

                if (std::find(boxesToMove.begin(), boxesToMove.end(), current) == boxesToMove.end())
                {
                    boxesToMove.push_back(current);
                }

                if (d == Direction::LEFT || d == Direction::RIGHT)
                {
                    if (d == Direction::RIGHT)
                    {
                        facesToCheck.insert(std::make_pair(current.first + (directions[d].first * 2), current.second + (directions[d].second * 2)));
                    }
                    else
                    {
                        facesToCheck.insert(std::make_pair(current.first + directions[d].first, current.second + directions[d].second));
                    }
                    
                }
                else if (d == Direction::UP || d == Direction::DOWN)
                {
                    facesToCheck.insert(std::make_pair(current.first + (directions[d].first), current.second + (directions[d].second)));
                    facesToCheck.insert(std::make_pair(current.first + 1 + (directions[d].first), current.second + (directions[d].second)));
                }
            }
        }
        
        if (canMove)
        {
            for (const std::pair<int, int> & boxLocation : boxesToMove)
            {
                map[boxLocation.second][boxLocation.first] = '.';
                map[boxLocation.second][boxLocation.first + 1] = '.';
            }

            for (const std::pair<int, int> & boxLocation : boxesToMove)
            {
                map[boxLocation.second + directions[d].second][boxLocation.first + directions[d].first] = '[';
                map[boxLocation.second + directions[d].second][boxLocation.first + 1 + directions[d].first] = ']';
            }

            map[robotLocation.second][robotLocation.first] = '.';
            map[newRobotLocation.second][newRobotLocation.first] = '@';
            robotLocation = newRobotLocation;
        }
    }
    
    result = getGPSCoordinates(map);
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day15_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");
    assert(part1(testinput) == 2028);

    FileHandler testFileHandler2("input-files/2024/day15_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n\n");
    assert(part1(testinput2) == 10092);

    FileHandler fileHandler("input-files/2024/day15.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput2) == 9021);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}