#include <iostream>
#include <chrono>

#include <cassert>

#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int,int> Coordinate;

void output(std::map<Coordinate, char> seaCucumberMap, int boundX, int boundY)
{
    for (int y = 0; y < boundY; y++)
    {
        for (int x = 0; x < boundX; x++)
        {
            if (seaCucumberMap.find(std::make_pair(x,y)) != seaCucumberMap.end())
            {
                std::cout << seaCucumberMap[std::make_pair(x,y)];
            }
            else 
            {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

bool executeStep(std::map<Coordinate, char>& seaCucumberMap, int boundX, int boundY)
{
    std::vector<char> order {'>', 'v'};

    bool moved = false;

    for (char currentDirection : order)
    {
        std::map<Coordinate, char> seaCucumberMapCopy = seaCucumberMap;
        for (std::pair<Coordinate, char> coordinateAndDirection : seaCucumberMapCopy)
        {
            if (coordinateAndDirection.second == currentDirection)
            {
                Coordinate newCoordinate;
                if (currentDirection == '>')
                {  
                    if (coordinateAndDirection.first.first+1 >= boundX)
                    {
                        newCoordinate = std::make_pair(0, coordinateAndDirection.first.second);
                    }
                    else
                    {
                        newCoordinate = std::make_pair(coordinateAndDirection.first.first+1, coordinateAndDirection.first.second);
                    }
                }
                else if (currentDirection == 'v')
                {  
                    if (coordinateAndDirection.first.second+1 >= boundY)
                    {
                    newCoordinate = std::make_pair(coordinateAndDirection.first.first, 0);
                    }
                    else
                    {
                        newCoordinate = std::make_pair(coordinateAndDirection.first.first, coordinateAndDirection.first.second + 1);
                    }
                }
                
                if (seaCucumberMapCopy.find(newCoordinate) == seaCucumberMapCopy.end())
                {

                    moved = true;
                    seaCucumberMap.erase(coordinateAndDirection.first);
                    seaCucumberMap[newCoordinate] = coordinateAndDirection.second;
                }   
            }
        }
    }

    return moved;
}

int getAmountOfStepsUntilStopMoving(std::map<Coordinate, char> seaCucumberMap, int boundX, int boundY)
{
    bool moving = true;
    int step = 0;
    while(moving)
    {
        moving = executeStep(seaCucumberMap, boundX, boundY);
        step++;
    }
    
    return step;
}

std::map<Coordinate, char> parseInputToMap(std::vector<std::string> input)
{
    std::map<Coordinate, char> result;

    // top left is 0,0 bottom right is input[0].size(), input.size()
    for (int x = 0; x < input[0].size(); x++)
    {
        for (int y = 0; y < input.size(); y++)
        {
            if (input[y][x] != '.')
            {
                result[std::make_pair(x,y)] = input[y][x];
            }
        }   
    }

    return result;
}

int main(void)
{
    std::vector<std::string> testInput2 = {"v...>>.vv>", ".vv>>.vv..", ">>.>v>...v", ">>v>>.>.v.", "v>v.vv.v..", ">.>>..v...", ".vv..>.>v.", "v.v..>>v.v", "....v..v.>"};
    assert(getAmountOfStepsUntilStopMoving(parseInputToMap(testInput2), testInput2[0].size(), testInput2.size()) == 58);

    FileHandler fileHandler("input-files/2021/day25.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 25, puzzle 1: " << std::flush << getAmountOfStepsUntilStopMoving(parseInputToMap(input), input[0].size(), input.size()) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}