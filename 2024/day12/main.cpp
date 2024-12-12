#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <set>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool isInBounds(const int & x, const int & y, const std::vector<std::string> & map)
{
    return x >= 0 && x < map[y].size() && y >= 0 && y < map.size();
}

void getRegion(const int & x, const int & y, const std::vector<std::string> & map, std::set<std::pair<int, int>> & region, std::set<std::pair<int, int>> & handled)
{
    std::vector<std::pair<int, int>> directions = { {0,-1}, {0,1}, {-1,0}, {1,0} }; // up, down, left, right
    if (handled.find(std::make_pair(x,y)) != handled.end())
    {
        return;
    }

    region.insert(std::make_pair(x,y));
    handled.insert(std::make_pair(x,y));

    for (const std::pair<int, int> direction : directions)
    {
        int newX = x + direction.first;
        int newY = y + direction.second;
        if (isInBounds(newX, newY, map))
        {
            if (map[y][x] == map[newY][newX])
            {
                getRegion(newX, newY, map, region, handled);
            }
        }
    }
}

int calculatePerimeter(const std::set<std::pair<int, int>> & region)
{
    std::vector<std::pair<int, int>> directions = { {0,-1}, {0,1}, {-1,0}, {1,0} }; // up, down, left, right
    int perimeterSize = 0;
    for (const auto & plant : region)
    {
        for (const std::pair<int, int> direction : directions)
        {
            if (region.find(std::make_pair(plant.first + direction.first, plant.second + direction.second)) == region.end())
            {
                perimeterSize++;
            }
        }
    }
    return perimeterSize;
}

// calculate sides by calculating the amount of corners in the perimeter
int calculateSides(const std::set<std::pair<int, int>> & region)
{
    int sides = 0;
    std::map<std::pair<int, int>, std::pair<int, int>> fencesFromTo;
    for (const auto & plant : region)
    {
        int x = 0;

        bool upNeighbour = region.find(std::make_pair(plant.first, plant.second - 1)) != region.end();
        bool downNeighbour = region.find(std::make_pair(plant.first, plant.second + 1)) != region.end();
        bool leftNeighbour = region.find(std::make_pair(plant.first - 1, plant.second)) != region.end();
        bool rightNeighbour = region.find(std::make_pair(plant.first + 1, plant.second)) != region.end();
        bool leftUpNeighbour = region.find(std::make_pair(plant.first - 1, plant.second - 1)) != region.end();
        bool rightUpNeighbour = region.find(std::make_pair(plant.first + 1, plant.second - 1)) != region.end();
        bool leftDownNeighbour = region.find(std::make_pair(plant.first - 1, plant.second + 1)) != region.end();
        bool rightDownNeighbour = region.find(std::make_pair(plant.first + 1, plant.second + 1)) != region.end();
        
        if (!upNeighbour && !downNeighbour && !leftNeighbour && !rightNeighbour)
        {
            sides += 4;
            x += 4;
        }

        // 2 outer corners
        if (!upNeighbour && !leftNeighbour && !downNeighbour && rightNeighbour) { sides += 2; x += 2; }
        if (!upNeighbour && !rightNeighbour && !downNeighbour && leftNeighbour) { sides += 2; x += 2; }
        if (!leftNeighbour && !upNeighbour && !rightNeighbour && downNeighbour) { sides += 2; x += 2; }
        if (!leftNeighbour && !downNeighbour && !rightNeighbour && upNeighbour) { sides += 2; x += 2; }
        
        // inner corner
        if (upNeighbour && leftNeighbour && !leftUpNeighbour) { sides += 1; x += 1; }
        if (upNeighbour && rightNeighbour && !rightUpNeighbour) { sides += 1; x += 1; }
        if (downNeighbour && leftNeighbour && !leftDownNeighbour) { sides += 1; x += 1; }
        if (downNeighbour && rightNeighbour && !rightDownNeighbour) { sides += 1; x += 1; }

        //outer corner
        if (upNeighbour && leftNeighbour && !rightNeighbour && !downNeighbour) { sides += 1; x += 1; }
        if (upNeighbour && rightNeighbour && !leftNeighbour && !downNeighbour) { sides += 1; x += 1; }
        if (downNeighbour && leftNeighbour && !rightNeighbour && !upNeighbour) { sides += 1; x += 1; }
        if (downNeighbour && rightNeighbour && !leftNeighbour && !upNeighbour) { sides += 1; x += 1; }
    }
    
    return sides;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;

    std::set<std::pair<int, int>> handled;
    std::vector<std::set<std::pair<int, int>>> regions;
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            std::set<std::pair<int, int>> currentRegion;
            getRegion(x, y, input, currentRegion, handled);
            if (!currentRegion.empty())
            {
                regions.push_back(currentRegion);
            }
        }
    }

    for (const auto & region : regions)
    {
        result += region.size() * calculatePerimeter(region);
    }
    
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    
    std::set<std::pair<int, int>> handled;
    std::vector<std::set<std::pair<int, int>>> regions;
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            std::set<std::pair<int, int>> currentRegion;
            getRegion(x, y, input, currentRegion, handled);
            if (!currentRegion.empty())
            {
                regions.push_back(currentRegion);
            }
        }
    }

    for (const auto & region : regions)
    {
        result += region.size() * calculateSides(region);
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day12_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 140);

    FileHandler testFileHandler2("input-files/2024/day12_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n");
    assert(part1(testinput2) == 772);

    FileHandler testFileHandler3("input-files/2024/day12_testinput3.txt");
    std::vector<std::string> testinput3 = StringParser::toVector(testFileHandler3.getBuffer(), "\n");
    assert(part1(testinput3) == 1930);
    
    FileHandler fileHandler("input-files/2024/day12.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
 
    assert(part2(testinput) == 80);
    assert(part2(testinput2) == 436);
    assert(part2(testinput3) == 1206);

    FileHandler testFileHandler4("input-files/2024/day12_testinput4.txt");
    std::vector<std::string> testinput4 = StringParser::toVector(testFileHandler4.getBuffer(), "\n");
    assert(part2(testinput4) == 236);

    FileHandler testFileHandler5("input-files/2024/day12_testinput5.txt");
    std::vector<std::string> testinput5 = StringParser::toVector(testFileHandler5.getBuffer(), "\n");
    assert(part2(testinput5) == 368);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}