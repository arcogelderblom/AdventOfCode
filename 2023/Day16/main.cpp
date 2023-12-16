#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <utility>
#include <list>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

enum Direction
{
    DOWN,
    LEFT,
    UP,
    RIGHT
};

typedef std::pair<Coordinate, Direction> Beam;

void nextStep(Beam & beam)
{
    switch (beam.second)
    {
        case (Direction::DOWN) :
        {
            beam.first.second += 1;
            break;
        }
        case (Direction::LEFT) :
        {
            beam.first.first -= 1;
            break;
        }
        case (Direction::UP) :
        {
            beam.first.second -= 1;
            break;
        }
        case (Direction::RIGHT) :
        {
            beam.first.first += 1;
            break;
        }
    }
}

void performSteps(const std::vector<std::string> & input, Beam startBeam, std::set<Coordinate> & allLocations)
{
    std::vector<Beam> allBeamLocations;
    std::list<Beam> beams { startBeam };
    while (!beams.empty())
    {
        Beam & currentBeam = beams.back();
        bool newBeamCreated = false;
        Beam newBeam;
        nextStep(currentBeam);

        // check if out of bounds
        if (currentBeam.first.first < 0 || currentBeam.first.first >= input.size() ||
            currentBeam.first.second < 0 || currentBeam.first.second >= input[0].size())
        {
            beams.pop_back();
            continue;
        }

        char currentPosition = input[currentBeam.first.second][currentBeam.first.first];
        
        if (currentPosition == '\\')
        {
            switch (currentBeam.second)
            {
                case (Direction::DOWN) :
                {
                    currentBeam.second = Direction::RIGHT;
                    break;
                }
                case (Direction::LEFT) :
                {
                    currentBeam.second = Direction::UP;
                    break;
                }
                case (Direction::UP) :
                {
                    currentBeam.second = Direction::LEFT;
                    break;
                }
                case (Direction::RIGHT) :
                {
                    currentBeam.second = Direction::DOWN;
                    break;
                }
            }
        }
        else if (currentPosition == '/')
        {
            switch (currentBeam.second)
            {
                case (Direction::DOWN) :
                {
                    currentBeam.second = Direction::LEFT;
                    break;
                }
                case (Direction::LEFT) :
                {
                    currentBeam.second = Direction::DOWN;
                    break;
                }
                case (Direction::UP) :
                {
                    currentBeam.second = Direction::RIGHT;
                    break;
                }
                case (Direction::RIGHT) :
                {
                    currentBeam.second = Direction::UP;
                    break;
                }
            }
        }
        else if (currentPosition == '|')
        {
            if (currentBeam.second == Direction::LEFT || currentBeam.second == Direction::RIGHT)
            {
                currentBeam.second = Direction::UP;
                newBeam = currentBeam;
                newBeam.second = Direction::DOWN;
                newBeamCreated = true;
            }
        }
        else if (currentPosition == '-')
        {
            if (currentBeam.second == Direction::DOWN || currentBeam.second == Direction::UP)
            {
                currentBeam.second = Direction::LEFT;
                newBeam = currentBeam;
                newBeam.second = Direction::RIGHT;
                newBeamCreated = true;
            }
        }
        
        if (std::find(allBeamLocations.begin(), allBeamLocations.end(), currentBeam) != allBeamLocations.end())
        {
            beams.pop_back();
        }
        else
        {
            allBeamLocations.push_back(currentBeam);
            allLocations.emplace(currentBeam.first);
        }

        // check if there is a new beam created, if so, add to vector. Do this last because of the push back otherwise kills the currrentBeam reference
        if (newBeamCreated)
        {
            beams.push_back(newBeam);
        }
    }
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    Beam startBeam(std::make_pair(-1, 0), Direction::RIGHT);
    std::set<Coordinate> allLocations;
    performSteps(input, startBeam, allLocations);
    result = allLocations.size();
    
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    int maxResult = 0;
    for (int i = 0; i < input.size(); i++)
    {
        Beam startBeam(std::make_pair(-1, i), Direction::RIGHT);
        std::set<Coordinate> allLocations;
        performSteps(input, startBeam, allLocations);
        if (allLocations.size() > maxResult)
        {
            maxResult = allLocations.size();
        }
    }
    
    for (int i = 0; i < input.size(); i++)
    {
        Beam startBeam(std::make_pair(input[0].size(), i), Direction::LEFT);
        std::set<Coordinate> allLocations;
        performSteps(input, startBeam, allLocations);
        if (allLocations.size() > maxResult)
        {
            maxResult = allLocations.size();
        }
    }
    
    for (int i = 0; i < input[0].size(); i++)
    {
        Beam startBeam(std::make_pair(i, -1), Direction::DOWN);
        std::set<Coordinate> allLocations;
        performSteps(input, startBeam, allLocations);
        if (allLocations.size() > maxResult)
        {
            maxResult = allLocations.size();
        }
    }
    
    for (int i = 0; i < input[0].size(); i++)
    {
        Beam startBeam(std::make_pair(i, input.size()), Direction::UP);
        std::set<Coordinate> allLocations;
        performSteps(input, startBeam, allLocations);
        if (allLocations.size() > maxResult)
        {
            maxResult = allLocations.size();
        }
    }
    
    result = maxResult;
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day16_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 46);

    FileHandler fileHandler("input-files/2023/day16.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    assert(part2(testInput) == 51);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}