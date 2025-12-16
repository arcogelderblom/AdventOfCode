#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include <set>

unsigned long long part1(const std::vector<std::string> & input)
{
    unsigned long long result = 0;

    std::vector<std::pair<long long, long long>> coordinates;
    for (const std::string & line : input)
    {
        std::vector<long long> coordinateVec = StringParser::toLongLongVector(line, ",");
        coordinates.push_back({coordinateVec[0], coordinateVec[1]});
    }

    for (int i = 0; i < coordinates.size(); i++)
    {
        for (int j = i + 1; j < coordinates.size(); j++)
        {
            long long area = (std::abs(coordinates[i].first - coordinates[j].first) + 1) * (std::abs(coordinates[i].second - coordinates[j].second) + 1);
            if (area > result)
            {
                result = area;
            }
        }
    }

    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0; 

    // get smallest y with smallest x (that is then definitely a corner going from bottom to right, deterministically setting the correct side as 'outer side')
    long long smallestY = std::numeric_limits<long long>::max();    
    std::vector<std::pair<long long, long long>> coordinates;
    for (const std::string & line : input)
    {
        std::vector<long long> coordinateVec = StringParser::toLongLongVector(line, ",");
        coordinates.push_back({coordinateVec[0], coordinateVec[1]});
        if (coordinateVec[1] < smallestY)
        {
            smallestY = coordinateVec[1];
        }
    }

    int startPointIndex = 0;
    long long currentSmallestX = std::numeric_limits<long long>::max();
    for (int i = 0; i < coordinates.size(); i++)
    {
        if (coordinates[i].second == smallestY)
        {
            if (coordinates[i].first < currentSmallestX)
            {
                startPointIndex = i;
                currentSmallestX = coordinates[i].first;
            }
        }
    }

    std::set<std::pair<long long, long long>> redGreenTilesBorder;
    for (int i = 0; i < coordinates.size(); i++)
    {
        std::pair<long long, long long> first = coordinates[i];
        std::pair<long long, long long> second;
        if (i == coordinates.size() - 1)
        {
            second = coordinates[0];
        }
        else
        {
            second = coordinates[i+1];
        }

        if (first.first == second.first)
        {
            for (int d = 0; d <= std::abs(first.second - second.second); d++)
            {
                int y = (first.second < second.second ? first.second : second.second);
                y += d;
                redGreenTilesBorder.insert({first.first, y});
            }
        }
        else if (first.second == second.second)
        {
            for (int d = 0; d <= std::abs(first.first - second.first); d++)
            {
                int x = (first.first < second.first ? first.first : second.first);
                x += d;
                redGreenTilesBorder.insert({x, first.second});
            }
        }
    }

    // start at the startpointindex, keep track of direction and create the outsideborder
    std::set<std::pair<long long, long long>> outsideBorder;
    std::vector<std::pair<int, int>> directions = { {-1, -1}, {0, -1}, {1, -1},
                                                    {-1, 0},           {1, 0},
                                                    {-1, 1},  {0, 1},  {1, 1}};
    
    enum DIR { LEFT, RIGHT, UP, DOWN };
    DIR d = RIGHT;
    for (int i = startPointIndex; i != (startPointIndex != 0 ? startPointIndex - 1 : coordinates.size() - 1); i++)
    {
        std::pair<long long, long long> first = coordinates[i];
        std::pair<long long, long long> second;
        if (i == coordinates.size() - 1)
        {
            second = coordinates[0];
        }
        else
        {
            second = coordinates[i+1];
        }

        if (first.first == second.first)
        {
            d = (first.second - second.second < 0 ? DOWN : UP);
            for (int dy = 0; dy <= std::abs(first.second - second.second); dy++)
            {
                int y = (first.second < second.second ? first.second : second.second);
                y += dy;
                if (d == UP)
                {
                    if (!redGreenTilesBorder.contains({first.first - 1, y}))
                    {
                        outsideBorder.insert({first.first - 1, y});
                    }
                }
                else if (d == DOWN)
                {
                    if (!redGreenTilesBorder.contains({first.first + 1, y}))
                    {
                        outsideBorder.insert({first.first + 1, y});
                    }
                }
            }
        }
        else if (first.second == second.second)
        {
            d = (first.first - second.first < 0 ? RIGHT : LEFT);
            for (int dx = 0; dx <= std::abs(first.first - second.first); dx++)
            {
                int x = (first.first < second.first ? first.first : second.first);
                x += dx;
                if (d == RIGHT)
                {
                    if (!redGreenTilesBorder.contains({x, first.second - 1}))
                    {
                        outsideBorder.insert({x, first.second - 1});
                    }
                }
                else if (d == LEFT)
                {
                    if (!redGreenTilesBorder.contains({x, first.second + 1}))
                    {
                        outsideBorder.insert({x, first.second + 1});
                    }
                }
            }
        }


        if (i == coordinates.size() - 1)
        {
            i = -1; // i becomes 0 after increment succesfully looping around
        }
    }

    std::set<std::pair<long long, std::pair<std::pair<long long, long long>, std::pair<long long, long long>>>> areaWithCorners; // {area, {{x,y}, {x,y}}}
    for (int i = 0; i < coordinates.size(); i++)
    {
        for (int j = i + 1; j < coordinates.size(); j++)
        {
            areaWithCorners.insert({(std::abs(coordinates[i].first - coordinates[j].first) + 1) * (std::abs(coordinates[i].second - coordinates[j].second) + 1), {coordinates[i], coordinates[j]}});
        }
    }

    for (auto it = areaWithCorners.rbegin(); it != areaWithCorners.rend(); it++)
    {
        bool contained = true;
        for (int dy = 0; dy <= std::abs((*it).second.first.second - (*it).second.second.second); dy++)
        {
            int y = ((*it).second.first.second < (*it).second.second.second ? (*it).second.first.second : (*it).second.second.second);
            y += dy;
            if (outsideBorder.contains({(*it).second.first.first, y}))
            {
                contained = false;
                break;
            }
            if (outsideBorder.contains({(*it).second.second.first, y}))
            {
                contained = false;
                break;
            }
        }

        if (!contained)
        {
            continue;
        }
        
        for (int dx = 0; dx <= std::abs((*it).second.first.first - (*it).second.second.first); dx++)
        {
            int x = ((*it).second.first.first < (*it).second.second.first ? (*it).second.first.first : (*it).second.second.first);
            x += dx;

            if (outsideBorder.contains({x, (*it).second.first.second}))
            {
                contained = false;
                break;
            }
            if (outsideBorder.contains({x, (*it).second.second.second}))
            {
                contained = false;
                break;
            }
        }
        if (contained)
        {
            return (*it).first;
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day09_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 50);

    FileHandler fileHandler("input-files/2025/day09.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 24);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}