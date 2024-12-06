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
    U, // up
    R, // right
    D, // down
    L // left
};

// returns x,y coordinate where y is counted from top to bottom
std::pair<int, int> getPosition(char c, const std::vector<std::string> & map)
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

bool isInBounds(const std::pair<int, int> & position, const std::vector<std::string> & floorplan)
{
    return position.first >= 0 && position.first < floorplan[position.second].size() && position.second >= 0 && position.second < floorplan.size();
}

std::set<std::tuple<int, int, Direction>> getAllVisitedLocations(const std::vector<std::string> & floorplan, std::pair<int, int> positionGuard, Direction direction)
{
    std::map<Direction, std::pair<int, int>> directions;
    directions[U] = std::make_pair(0, -1);
    directions[R] = std::make_pair(1, 0);
    directions[D] = std::make_pair(0, 1);
    directions[L] = std::make_pair(-1, 0);

    std::set<std::tuple<int,int,Direction>> visitedPositions;

    while (isInBounds(positionGuard, floorplan))
    {
        visitedPositions.insert(std::make_tuple(positionGuard.first, positionGuard.second, direction));
        std::pair<int, int> nextPosition = std::make_pair((positionGuard.first + directions[direction].first), (positionGuard.second + directions[direction].second));
        while (floorplan[nextPosition.second][nextPosition.first] == '#')
        {
            if (direction == L)
            {
                direction = U;
            }
            else
            {
                direction = static_cast<Direction>((int)direction + 1);
            }
            nextPosition = std::make_pair((positionGuard.first + directions[direction].first), (positionGuard.second + directions[direction].second));
        }
        positionGuard = nextPosition;
    }
    return visitedPositions;
}

int part1(const std::vector<std::string> & input) 
{
    std::pair<int, int> positionGuard = getPosition('^', input);
    Direction currentDirection = U;

    std::set<std::tuple<int, int, Direction>> visitedPositionsGuard = getAllVisitedLocations(input, positionGuard, currentDirection);

    std::set<std::pair<int, int>> uniqueLocations;
    std::for_each(visitedPositionsGuard.begin(), visitedPositionsGuard.end(), [&](const std::tuple<int, int, Direction> & elem){ uniqueLocations.insert(std::make_pair(std::get<0>(elem), std::get<1>(elem))); });

    return uniqueLocations.size();
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    
    std::map<Direction, std::pair<int, int>> directions;
    directions[U] = std::make_pair(0, -1);
    directions[R] = std::make_pair(1, 0);
    directions[D] = std::make_pair(0, 1);
    directions[L] = std::make_pair(-1, 0);

    std::pair<int, int> startPosition = getPosition('^', input);
    Direction startDirection = U;

    std::set<std::tuple<int, int, Direction>> visitedLocations = getAllVisitedLocations(input, startPosition, startDirection);
    std::set<std::pair<int, int>> potentialBlockedLocations;
    std::for_each(visitedLocations.begin(), visitedLocations.end(), [&](const std::tuple<int, int, Direction> & elem){ potentialBlockedLocations.insert(std::make_pair(std::get<0>(elem), std::get<1>(elem))); });

    // only place obstacle in places where the guard actually walks, except for startlocation
    potentialBlockedLocations.erase(std::make_pair(startPosition.first, startPosition.second));

    for (const std::pair<int, int> & blockedLocation : potentialBlockedLocations)
    {
        std::pair<int, int> currentPosition = startPosition;
        Direction currentDirection = startDirection;
        std::set<std::tuple<int, int, Direction>> steps;

        std::vector<std::string> floorplan = input;
        floorplan[blockedLocation.second][blockedLocation.first] = '#';
        
        // as long as we are within bounds and our current position and direction is somewhere we haven't been yet, continue
        while (isInBounds(currentPosition, floorplan) && steps.find(std::make_tuple(currentPosition.first, currentPosition.second, currentDirection)) == steps.end())
        {
            steps.insert(std::make_tuple(currentPosition.first, currentPosition.second, currentDirection));
            std::pair<int, int> nextPosition = std::make_pair((currentPosition.first + directions[currentDirection].first), (currentPosition.second + directions[currentDirection].second));
            
            while (floorplan[nextPosition.second][nextPosition.first] == '#')
            {
                if (currentDirection == L)
                {
                    currentDirection = U;
                }
                else
                {
                    currentDirection = static_cast<Direction>((int)currentDirection + 1);
                }
                nextPosition = std::make_pair((currentPosition.first + directions[currentDirection].first), (currentPosition.second + directions[currentDirection].second));
            }

            currentPosition = nextPosition;
        }

        if (isInBounds(currentPosition, floorplan))
        {
            // not out of bounds so detected a loop
            result++;
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day06_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 41);

    FileHandler fileHandler("input-files/2024/day06.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 6);
    
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}