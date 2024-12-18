#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool isInBounds(const std::pair<int, int> & coordinate, const int & maxX, const int & maxY)
{
    return coordinate.first >= 0 && coordinate.first <= maxX && coordinate.second >= 0 && coordinate.second <= maxY;
}

int distanceTo(const std::pair<int, int> & first, const std::pair<int, int> & second)
{
    return std::abs(first.first - second.first) + std::abs(first.second - second.second);
}

int getShortestPath(const std::pair<int, int> & finish, const std::set<std::pair<int, int>> & corruptedCoordinates)
{
    std::pair<int, int> start = {0, 0};

    // pair consists of <current steps + min steps to end, current coordinate>
    std::set<std::pair<int, std::pair<int, int>>> next = { { 0 + distanceTo(start, finish), start } }; 
    std::vector<std::pair<int, int>> directions = { { 0, -1 }, // up
                                                    { 0, 1 },  // down
                                                    { -1, 0 }, // left
                                                    { 1, 0 } };// right
    std::pair<int, std::pair<int, int>> current = *next.begin();
    next.erase(current);
    while (current.second != finish && current.first < (finish.first * finish.second))
    {
        for (const std::pair<int, int> & d : directions)
        {
            std::pair<int, int> nextCoordinate = std::make_pair(current.second.first + d.first, current.second.second + d.second);
            if (corruptedCoordinates.find(nextCoordinate) == corruptedCoordinates.end() && isInBounds(nextCoordinate, finish.first, finish.second))
            {
                next.insert(std::make_pair(current.first - distanceTo(current.second, finish) + distanceTo(nextCoordinate, finish) + 1, nextCoordinate));
            }
        }
        if (next.size() > 0)
        {
            current = *next.begin();
            next.erase(current);
        }
    }
    if (current.second == finish)
    {
        return current.first;
    }
    return 0;
}

int part1(const std::vector<std::string> & input, int bytes, std::pair<int, int> finish) 
{
    int result = 0;
    std::set<std::pair<int, int>> corruptedCoordinates;
    for (int i = 0; i < bytes; i++)
    {
        std::pair<int, int> corruptedCoordinate = std::make_pair(std::stoi(input[i].substr(0, input[i].find(','))), std::stoi(input[i].substr(input[i].find(',') + 1)));
        corruptedCoordinates.insert(corruptedCoordinate);
    }
    result = getShortestPath(finish, corruptedCoordinates);
    return result;
}

std::string part2(const std::vector<std::string> & input, std::pair<int, int> finish) 
{
    std::string result = "";
    std::set<std::pair<int, int>> corruptedCoordinates;
    std::string currentCoordinate;
    for (int i = 0; i < input.size(); i++)
    {
        std::pair<int, int> corruptedCoordinate = std::make_pair(std::stoi(input[i].substr(0, input[i].find(','))), std::stoi(input[i].substr(input[i].find(',') + 1)));
        corruptedCoordinates.insert(corruptedCoordinate);
    }
    for (int i = input.size() - 1; i >= 0; i--)
    {
        currentCoordinate = input[i];
        std::pair<int, int> corruptedCoordinate = std::make_pair(std::stoi(currentCoordinate.substr(0, currentCoordinate.find(','))), std::stoi(currentCoordinate.substr(currentCoordinate.find(',') + 1)));
        corruptedCoordinates.erase(corruptedCoordinate);
        if (getShortestPath(finish, corruptedCoordinates))
        {
            result = currentCoordinate;
            break;
        }
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day18_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    
    assert(part1(testinput, 12, std::make_pair(6, 6)) == 22);

    FileHandler fileHandler("input-files/2024/day18.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 1: " << std::flush << part1(input, 1024, std::make_pair(70, 70)) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput, std::make_pair(6, 6)) == "6,1");

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 2: " << std::flush << part2(input, std::make_pair(70, 70)) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}