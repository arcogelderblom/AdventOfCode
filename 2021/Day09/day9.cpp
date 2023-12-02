#include <iostream>
#include <map>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <set>
#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

std::map<Coordinate, int> getAdjacentPositionsWithValue(std::vector<std::string> map, Coordinate startPoint)
{
    std::map<Coordinate , int> result;
    if (startPoint.first != 0)
    {
        Coordinate current = std::make_pair(startPoint.second, startPoint.first - 1);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    if (startPoint.second != 0)
    {
        Coordinate current = std::make_pair(startPoint.second - 1, startPoint.first);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    if (startPoint.first != map[startPoint.second].size() - 1)
    {
        Coordinate current = std::make_pair(startPoint.second, startPoint.first + 1);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    if (startPoint.second != map.size() - 1)
    {
        Coordinate current = std::make_pair(startPoint.second + 1, startPoint.first);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    return result;
}

std::vector<Coordinate> findLowPointsCoordinates(std::vector<std::string> map)
{
    std::vector<Coordinate> result;
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            std::vector<int> adjacentHeights;
            for (std::pair<Coordinate, int> adjacentPositionWithValue : getAdjacentPositionsWithValue(map, std::make_pair(x, y)))
            {
                adjacentHeights.push_back(adjacentPositionWithValue.second);
            }
            int currentHeight = map[y][x] - '0';
            if (std::count_if(adjacentHeights.begin(), adjacentHeights.end(), [&](const int adjacentHeight){ return currentHeight < adjacentHeight; }) == adjacentHeights.size())
            {
                result.push_back(std::make_pair(x, y));
            }
        }
    }
    return result;
}

unsigned long getSumRiskLevels(std::vector<std::string> map)
{
    unsigned long sum = 0;
    for (Coordinate lowPoint : findLowPointsCoordinates(map))
    {
        sum += 1 + (map[lowPoint.second][lowPoint.first] - '0');
    }
    
    return sum;
}
std::set<Coordinate> pointsInBasins;
int getBasinSize(std::vector<std::string> map, Coordinate startPoint)
{
    std::set<Coordinate> pointsInBasin;
    pointsInBasin.insert(startPoint);
    pointsInBasins.insert(startPoint);
    std::set<Coordinate> unvisitedAdjacentPoints;
    unvisitedAdjacentPoints.insert(startPoint);
    while (unvisitedAdjacentPoints.size() > 0)
    {
        std::map<Coordinate, int> adjacentPointsWithValue = getAdjacentPositionsWithValue(map, *unvisitedAdjacentPoints.begin());
        int currentValue = map[unvisitedAdjacentPoints.begin()->second][unvisitedAdjacentPoints.begin()->first] - '0';
        unvisitedAdjacentPoints.erase(unvisitedAdjacentPoints.begin());
        for (std::pair<Coordinate, int> adjacentPointWithValue : adjacentPointsWithValue)
        {
            if (currentValue < adjacentPointWithValue.second && adjacentPointWithValue.second != 9)
            {
                unvisitedAdjacentPoints.insert(adjacentPointWithValue.first);
                pointsInBasin.insert(adjacentPointWithValue.first);
                pointsInBasins.insert(adjacentPointWithValue.first);
            }
        }
    }
    
    return pointsInBasin.size();
}

unsigned long getMultipliedThreeLargestBasins(std::vector<std::string> map)
{
    std::vector<int> largestBasinSizes;
    for (Coordinate lowPoint : findLowPointsCoordinates(map))
    {
        int basinSize = getBasinSize(map, lowPoint);
        
        if (largestBasinSizes.size() < 3)
        {
            largestBasinSizes.push_back(basinSize);
        }
        else if (largestBasinSizes.front() < basinSize)
        {
            largestBasinSizes[0] = basinSize;
        }
        std::sort(largestBasinSizes.begin(), largestBasinSizes.end());
    }

    unsigned long result = 1;
    for (int basinSize : largestBasinSizes)
    {
        result *= basinSize;
    }
    return result;
}

int main(void)
{
    std::vector<std::string> testMap = StringParser::toVector("2199943210\n3987894921\n9856789892\n8767896789\n9899965678", "\n");
    assert(getSumRiskLevels(testMap) == 15);
    
    FileHandler fileHandler("input-files/2021/day09.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 1: " << std::flush << getSumRiskLevels(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getMultipliedThreeLargestBasins(testMap) == 1134);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 2: " << std::flush << getMultipliedThreeLargestBasins(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
