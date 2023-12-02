#include <iostream>
#include <map>
#include <cassert>
#include <chrono>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

struct LinePoint
{
    Coordinate start;
    Coordinate end;
};

std::vector<LinePoint> toLinePoint(std::vector<std::string> linePoints) 
{
    std::vector<LinePoint> result;
    for (std::string linePointString : linePoints)
    {
        std::vector<std::string> startAndEnd = StringParser::toVector(linePointString, " -> ");
        std::vector<std::string> startString = StringParser::toVector(startAndEnd[0], ",");
        std::vector<std::string> endString = StringParser::toVector(startAndEnd[1], ",");
        Coordinate start, end;
        start.first = std::stoi(startString[0]);
        start.second = std::stoi(startString[1]);
        end.first = std::stoi(endString[0]);
        end.second = std::stoi(endString[1]);
        LinePoint linePoint;
        linePoint.start = start;
        linePoint.end = end;
        result.push_back(linePoint);
    }
    return result;
}

std::vector<LinePoint> filterVerticalAndHorizontalLines(std::vector<LinePoint> linesOfVents)
{
    std::vector<LinePoint> result;
    for (LinePoint lineOfVent : linesOfVents)
    {
        if (lineOfVent.start.first == lineOfVent.end.first || lineOfVent.start.second == lineOfVent.end.second)
        {
            result.push_back(lineOfVent);
        }
    }
    return result;
}

int findAmountOfOverlaps(std::vector<LinePoint> linePoints) 
{
    std::map<Coordinate, int> coordinatesWithVent;
    for (LinePoint linePoint : linePoints)
    {
        // horizontal line
        if (linePoint.start.first == linePoint.end.first)
        {
            int forLoopStart = linePoint.start.second;
            int forLoopEnd = linePoint.end.second;
            if (linePoint.start.second > linePoint.end.second)
            {
                forLoopStart = linePoint.end.second;
                forLoopEnd = linePoint.start.second;
            }
            
            for (int y = forLoopStart; y <= forLoopEnd; y++)
            {
                Coordinate currentCoordinate;
                currentCoordinate.first = linePoint.start.first;
                currentCoordinate.second = y;
                if (coordinatesWithVent.find(currentCoordinate) != coordinatesWithVent.end())
                {
                    coordinatesWithVent[currentCoordinate] = coordinatesWithVent[currentCoordinate]+1;
                }
                else 
                {
                    coordinatesWithVent[currentCoordinate] = 1;
                }
            }
        }
        // vertical line
        else if (linePoint.start.second == linePoint.end.second)
        {
            int forLoopStart = linePoint.start.first;
            int forLoopEnd = linePoint.end.first ;
            if (linePoint.start.first > linePoint.end.first)
            {
                forLoopStart = linePoint.end.first;
                forLoopEnd = linePoint.start.first;
            }
            
            for (int x = forLoopStart; x <= forLoopEnd; x++)
            {
                Coordinate currentCoordinate;
                currentCoordinate.first = x;
                currentCoordinate.second = linePoint.start.second;
                if (coordinatesWithVent.find(currentCoordinate) != coordinatesWithVent.end())
                {
                    coordinatesWithVent[currentCoordinate] = coordinatesWithVent[currentCoordinate]+1;
                }
                else 
                {
                    coordinatesWithVent[currentCoordinate] = 1;
                }
            }
        }
        // diagonal line
        else {
            int forLoopStartX = linePoint.start.first;
            int forLoopStartY = linePoint.start.second;
            int forLoopEndX = linePoint.end.first;
            int forLoopEndY = linePoint.end.second;

            if (forLoopStartX > forLoopEndX)
            {
                forLoopStartX = linePoint.end.first;
                forLoopEndX = linePoint.start.first;

                forLoopStartY = linePoint.end.second;
                forLoopEndY = linePoint.start.second;
            }
            if (forLoopStartY > forLoopEndY)
            {
                for (int x = forLoopStartX, y = forLoopStartY; x <= forLoopEndX && y >= forLoopEndY; x++, y--)
                {
                    Coordinate currentCoordinate;
                    currentCoordinate.first = x;
                    currentCoordinate.second = y;
                    if (coordinatesWithVent.find(currentCoordinate) != coordinatesWithVent.end())
                    {
                        coordinatesWithVent[currentCoordinate] = coordinatesWithVent[currentCoordinate]+1;
                    }
                    else 
                    {
                        coordinatesWithVent[currentCoordinate] = 1;
                    } 
                }
            }
            else 
            {
                for (int x = forLoopStartX, y = forLoopStartY; x <= forLoopEndX && y <= forLoopEndY; x++, y++)
                {
                    Coordinate currentCoordinate;
                    currentCoordinate.first = x;
                    currentCoordinate.second = y;
                    if (coordinatesWithVent.find(currentCoordinate) != coordinatesWithVent.end())
                    {
                        coordinatesWithVent[currentCoordinate] = coordinatesWithVent[currentCoordinate]+1;
                    }
                    else 
                    {
                        coordinatesWithVent[currentCoordinate] = 1;
                    } 
                }
            }
        }
    }

    int overlapping = 0;
    for (std::pair<Coordinate, int> coordinateWithVent : coordinatesWithVent)
    {
        if (coordinateWithVent.second > 1)
        {
            overlapping++;
        }
    }
    return overlapping;
}

int main(void)
{
    std::vector<LinePoint> linesOfVentsCoordinatesTest = toLinePoint({"0,9 -> 5,9", "8,0 -> 0,8", "9,4 -> 3,4", "2,2 -> 2,1", "7,0 -> 7,4", "6,4 -> 2,0", "0,9 -> 2,9", "3,4 -> 1,4", "0,0 -> 8,8", "5,5 -> 8,2"});
    assert(findAmountOfOverlaps(filterVerticalAndHorizontalLines(linesOfVentsCoordinatesTest)) == 5);

    FileHandler fileHandler("input-files/2021/day05.txt");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::vector<LinePoint> linesOfVentsCoordinates = toLinePoint(StringParser::toVector(fileHandler.getBuffer(), "\n"));
    std::cout << "Day 5, puzzle 1: " << std::flush << findAmountOfOverlaps(filterVerticalAndHorizontalLines(linesOfVentsCoordinates)) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(findAmountOfOverlaps(linesOfVentsCoordinatesTest) == 12);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 2: " << std::flush << findAmountOfOverlaps(linesOfVentsCoordinates) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}