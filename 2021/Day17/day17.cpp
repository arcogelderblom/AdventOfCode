#include <iostream>
#include <chrono>
#include <set>
#include <map>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

struct Probe
{
    Coordinate currentPosition = std::make_pair(0, 0);
    std::pair<int, int> velocity;
};

void executeStep(Probe& probe)
{
    probe.currentPosition.first += probe.velocity.first;
    probe.currentPosition.second += probe.velocity.second;
    if (probe.velocity.first > 0)
    {
        probe.velocity.first -= 1;
    }
    else if (probe.velocity.first < 0)
    {
        probe.velocity.first += 1;
    }
    probe.velocity.second -= 1;
}

std::vector<Coordinate> getTargetAreaBounds(std::string targetAreaString)
{
    std::vector<Coordinate> result;

    // target area: x=20..30, y=-10..-5
    std::vector<std::string> targetAreaSplitted = StringParser::toVector(targetAreaString, " ");
    std::vector<std::string> xStartAndEnd = StringParser::toVector(targetAreaSplitted[2].substr(2), "..");
    std::vector<std::string> yStartAndEnd = StringParser::toVector(targetAreaSplitted[3].substr(2), "..");
    
    int xStart = std::stoi(xStartAndEnd[0]);
    int xEnd = std::stoi(xStartAndEnd[1].substr(0, xStartAndEnd[1].size() - 1));
    int yStart = std::stoi(yStartAndEnd[0]);
    int yEnd = std::stoi(yStartAndEnd[1]);
    result.push_back(std::make_pair(xStart, xEnd));
    result.push_back(std::make_pair(yStart, yEnd));
    
    return result;
}


std::set<Coordinate> getTargetAreaCoordinates(std::string targetAreaString)
{
    std::set<Coordinate> result;

    // target area: x=20..30, y=-10..-5
    std::vector<std::string> targetAreaSplitted = StringParser::toVector(targetAreaString, " ");
    std::vector<std::string> xStartAndEnd = StringParser::toVector(targetAreaSplitted[2].substr(2), "..");
    std::vector<std::string> yStartAndEnd = StringParser::toVector(targetAreaSplitted[3].substr(2), "..");
    
    int xStart = std::stoi(xStartAndEnd[0]);
    int xEnd = std::stoi(xStartAndEnd[1].substr(0, xStartAndEnd[1].size() - 1));
    int yStart = std::stoi(yStartAndEnd[0]);
    int yEnd = std::stoi(yStartAndEnd[1]);
    
    for (int y = yStart; y <= yEnd; y++)
    {
        for (int x = xStart; x <= xEnd; x++)
        {
            result.insert(std::make_pair(x, y));
        }    
    }
    return result;
}

bool isInTargetArea(Probe probe, std::string targetAreaString)
{
    std::set<Coordinate> targetArea = getTargetAreaCoordinates(targetAreaString);
    return targetArea.find(probe.currentPosition) != targetArea.end();
}

bool surpassedTargetArea(Probe probe, std::string targetAreaString)
{
    std::vector<Coordinate> targetAreaBounds = getTargetAreaBounds(targetAreaString);
    if (probe.currentPosition.first <= targetAreaBounds[0].second && probe.currentPosition.first >= targetAreaBounds[0].first && probe.currentPosition.second < targetAreaBounds[1].first)
    {
        return true;
    }
    else if (probe.currentPosition.first > targetAreaBounds[0].second && probe.currentPosition.second >= targetAreaBounds[1].first && probe.currentPosition.second <= targetAreaBounds[1].second)
    {
        return true;
    }
    else if (probe.currentPosition.first > targetAreaBounds[0].second && probe.currentPosition.second < targetAreaBounds[1].first)
    {
        return true;
    }
    else if (probe.currentPosition.first < targetAreaBounds[0].second && probe.currentPosition.second < targetAreaBounds[1].first)
    {
        return true;
    }
    return false;
}

int getHighestY(std::string targetAreaString)
{
    std::vector<Coordinate> targetAreaBounds = getTargetAreaBounds(targetAreaString);
    std::map<std::pair<int,int>, int> velocityAndHighestY;
    for (int velocityY = targetAreaBounds[1].first; velocityY <= std::abs(targetAreaBounds[1].first); velocityY++)
    {
        for (int velocityX = 0; velocityX <= targetAreaBounds[0].second; velocityX++)
        {
            int endX = ((velocityX * velocityX) + velocityX) / 2;
            if (endX < targetAreaBounds[0].first || endX > targetAreaBounds[0].second)
            {
                continue;
            }
            
            Probe probe;
            std::pair<int, int> startVelocity = std::make_pair(velocityX, velocityY);
            probe.velocity = startVelocity;

            int highestY = 0;
            while (!isInTargetArea(probe, targetAreaString) && !surpassedTargetArea(probe, targetAreaString))
            {
                executeStep(probe);

                if (probe.currentPosition.second > highestY)
                {
                    highestY = probe.currentPosition.second;
                }

                if (isInTargetArea(probe, targetAreaString))
                {
                    velocityAndHighestY[startVelocity] = highestY;
                }
            }

            if (surpassedTargetArea(probe, targetAreaString) && velocityAndHighestY.find(std::make_pair(startVelocity.first - 1, startVelocity.second)) != velocityAndHighestY.end())
            {
                break;
            }
        }
    }
    int highestY = 0;
    for (std::pair<std::pair<int,int>, int> i : velocityAndHighestY)
    {
        if (i.second > highestY)
        {
            highestY = i.second;
        }
    }
    return highestY;
}

int getAmountDistinctInitialVelocities(std::string targetAreaString)
{
    std::vector<Coordinate> targetAreaBounds = getTargetAreaBounds(targetAreaString);
    
    int amountDistinctInitialVelocities = 0;
    for (int velocityY = targetAreaBounds[1].first; velocityY <= std::abs(targetAreaBounds[1].first); velocityY++)
    {
        bool foundCorrectVelocityLastValue = true;
        for (int velocityX = 0; velocityX <= targetAreaBounds[0].second; velocityX++)
        {
            int endX = ((velocityX * velocityX) + velocityX) / 2;
            if (velocityY > 5 && (endX < targetAreaBounds[0].first || endX > targetAreaBounds[0].second))
            {
                continue;
            }
            Probe probe;
            std::pair<int, int> startVelocity = std::make_pair(velocityX, velocityY);
            probe.velocity = startVelocity;

            while (!isInTargetArea(probe, targetAreaString) && !surpassedTargetArea(probe, targetAreaString))
            {
                executeStep(probe);
                if (isInTargetArea(probe, targetAreaString))
                {
                    foundCorrectVelocityLastValue = true;
                    amountDistinctInitialVelocities++;
                }
            }

            if (!foundCorrectVelocityLastValue)
            {
                continue;
            }
        }
    }
    return amountDistinctInitialVelocities;
}

int main(void)
{
    std::string testInput = "target area: x=20..30, y=-10..-5";
    assert(getHighestY(testInput) == 45);
    
    FileHandler fileHandler("input-files/2021/day17.txt");
    std::string input = StringParser::toVector(fileHandler.getBuffer(), "\n")[0];
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 1: " << std::flush << getHighestY(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getAmountDistinctInitialVelocities(testInput) == 112);    
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 17, puzzle 2: " << std::flush << getAmountDistinctInitialVelocities(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
