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
    RIGHT,
    DOWN,
    LEFT
};

int getDistance(const std::pair<int, int> & begin, const std::pair<int, int> & end, const Direction & d)
{
    if (begin == end) { return 0; }
    int diffX = end.first - begin.first;
    int diffY = end.second - begin.second;
    // case go straight
    if ((diffX == 0 && diffY > 0 && d == DOWN) ||
        (diffX == 0 && diffY < 0 && d == UP) ||
        (diffX < 0 && diffY == 0 && d == LEFT) ||
        (diffX > 0 && diffY == 0 && d == RIGHT))
    {
        return (std::abs(diffX) + std::abs(diffY));
    }
    // case at least one turn
    if ((diffY > 0 && diffX != 0 && d == DOWN) ||
        (diffY < 0 && diffX != 0 && d == UP) ||
        (diffX < 0 && diffY != 0 && d == LEFT) ||
        (diffX > 0 && diffY != 0 && d == RIGHT))
    {
        return (std::abs(diffX) + std::abs(diffY) + 1000);
    }
    // case at least two turns
    return (std::abs(diffX) + std::abs(diffY) + 2000);
}

int getTurnScore(int amount90DegTurns)
{
    if (amount90DegTurns == 2)
    {
        return 2000;
    }
    if (amount90DegTurns == 1 || amount90DegTurns == 3)
    {
        return 1000;
    }
    return 0;
}

std::pair<int, int> getPosition(const std::vector<std::string> & map, const char & c)
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == c)
            {
                return std::make_pair(x, y);
            }
        }   
    }
    return std::make_pair(-1, -1);
}

void output(const std::pair<int, int> & elem)
{
    std::cout << " (" << elem.first << ',' << elem.second << ") ";
}

void output(const std::vector<std::pair<int, int>> & vec)
{
    std::cout << " | vector contents = ";
    for (const auto & elem : vec)
    {
        output(elem);
    }
    std::cout << " | ";
}

void outputMap(std::vector<std::string> map, const std::vector<std::pair<int, int>> & route)
{
    std::cout << "Current map:" << std::endl;
    for (const std::pair<int, int> & point : route)
    {
        map[point.second][point.first] = 'X';
    }
    for (const std::string & row : map)
    {
        std::cout << '\t' << row << std::endl;
    }
    std::cout<<std::endl;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    
    std::map<Direction, std::pair<int, int>> directions = { { UP, { 0, -1 } },
                                                            { RIGHT, { 1, 0 } },
                                                            { DOWN, { 0, 1 } }, 
                                                            { LEFT, { -1, 0 } }  };
    
    std::pair<int, int> end = getPosition(input, 'S');
    std::pair<int, int> current = getPosition(input, 'E');
    Direction currentDirection = RIGHT;
    std::set<std::tuple<int, int, Direction, std::pair<int, int>>> nextCoordinates = { { 0, getDistance(current, end, currentDirection), currentDirection, current } };
    
    std::tuple<int, int, Direction, std::pair<int, int>> currentRoute;
    std::map<std::pair<int, int>, int> positionWithFastestWayToGetThere;
    positionWithFastestWayToGetThere[current] = 0;
    do
    {
        currentRoute = *nextCoordinates.begin();
        nextCoordinates.erase(currentRoute);

        current = std::get<3>(currentRoute);
        currentDirection = std::get<2>(currentRoute);

        for (int direction = 0; direction <= 3; direction++)
        {
            int newDirection = (int)currentDirection + direction;
            if (newDirection >= 4) { newDirection -= 4; }
            Direction d = (Direction)newDirection;
            std::pair<int, int> next = std::make_pair(current.first + directions[d].first, current.second + directions[d].second);
            if ((input[next.second][next.first] != '#'))
            {
                int newScore = std::get<0>(currentRoute);
                newScore += getTurnScore(direction);
                
                newScore += 1;
                auto newEntry = std::make_tuple(newScore, getDistance(next, end, d), d, next);

                if (positionWithFastestWayToGetThere.find(next) == positionWithFastestWayToGetThere.end() || newScore <= positionWithFastestWayToGetThere[next])
                {
                    positionWithFastestWayToGetThere[next] = newScore;
                    nextCoordinates.insert(newEntry);
                }
            }
        }
    } while (current != end);

    result = std::get<0>(currentRoute);
    return result;
}

int part2(const std::vector<std::string> & input, const int & bestScore) 
{
    int result = 0;
    
    std::map<Direction, std::pair<int, int>> directions = { { UP, { 0, -1 } },
                                                            { RIGHT, { 1, 0 } },
                                                            { DOWN, { 0, 1 } }, 
                                                            { LEFT, { -1, 0 } }  };
    std::pair<int, int> end = getPosition(input, 'E');
    std::pair<int, int> current = getPosition(input, 'S');
    Direction currentDirection = RIGHT;
    int score = 0;
    
    std::set<std::tuple<int, Direction, std::vector<std::pair<int, int>>>> nextCoordinates = { { score + getDistance(current, end, currentDirection), currentDirection, { current } } }; // tuple consists of: score + min distance to end, current direction, route
    std::tuple<int, Direction, std::vector<std::pair<int, int>>> currentRoute;

    std::set<std::pair<int, int>> allPositionsOfBestRoutes;
    std::map<std::pair<int, int>, std::pair<int, Direction>> positionWithFastestWayToGetThere;
    positionWithFastestWayToGetThere[current] = std::make_pair(0, currentDirection);
    
    do
    {
        currentRoute = *nextCoordinates.begin();
        nextCoordinates.erase(nextCoordinates.begin());

        std::vector<std::pair<int, int>> route = std::get<2>(currentRoute);
        current = *route.rbegin();
        currentDirection = std::get<1>(currentRoute);
        score = std::get<0>(currentRoute) - getDistance(current,end,currentDirection);
        
        for (int direction = 0; direction <= 3; direction++)
        {
            int newDirection = (int)currentDirection + direction;
            if (newDirection >= 4) { newDirection -= 4; }
            Direction d = (Direction)newDirection;
            std::pair<int, int> next = std::make_pair(current.first + directions[d].first, current.second + directions[d].second);
            if (input[next.second][next.first] != '#' && std::find(route.begin(), route.end(), next) == route.end())
            {
                int newScore = score;
                newScore += getTurnScore(direction);
                newScore += 1;
                
                auto newEntry = std::make_tuple(newScore + getDistance(next, end, d), d, route);
                std::get<2>(newEntry).push_back(next);
                if (newScore <= bestScore && (positionWithFastestWayToGetThere.find(next) == positionWithFastestWayToGetThere.end() || newScore <= positionWithFastestWayToGetThere[next].first + getTurnScore(std::abs(d - positionWithFastestWayToGetThere[next].second))))
                {
                    positionWithFastestWayToGetThere[next] = std::make_pair(newScore, d);
                    nextCoordinates.insert(newEntry);
                }
            }
        }

        if (current == end)
        {
            allPositionsOfBestRoutes.insert(std::get<2>(currentRoute).begin(), std::get<2>(currentRoute).end());
        }
    } while (!nextCoordinates.empty());
    
    result = allPositionsOfBestRoutes.size();
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day16_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 7036);

    FileHandler testFileHandler2("input-files/2024/day16_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n");
    assert(part1(testinput2) == 11048);

    FileHandler fileHandler("input-files/2024/day16.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 1: " << std::flush;
    int bestScore = part1(input);
    std::cout << bestScore << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput, 7036) == 45);
    assert(part2(testinput2, 11048) == 64);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 2: " << std::flush << part2(input, bestScore) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}