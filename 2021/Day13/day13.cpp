#include <iostream>
#include <chrono>
#include <set>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

std::set<Coordinate> toCoordinates(std::vector<std::string> stringCoordinates)
{
    std::set<Coordinate> coordinates;
    for (std::string item : stringCoordinates)
    {
        std::vector<std::string> splittedItem = StringParser::toVector(item, ",");
        coordinates.insert(std::make_pair(std::stoi(splittedItem[0]), std::stoi(splittedItem[1])));
    }
    return coordinates;
}

std::set<Coordinate> executeInstructions(std::set<Coordinate> dots, std::vector<std::string> instructions, int instructionsToExecute)
{
    for (int currentInstruction = 0; currentInstruction < instructionsToExecute; currentInstruction++)
    {
        char foldAlong = instructions[currentInstruction].substr(strlen("fold along "))[0];
        int num = std::stoi(instructions[currentInstruction].substr(strlen("fold along ") + 2));
        std::set<Coordinate> dotsCopy = dots;
        for (Coordinate dot : dotsCopy)
        {
            if (foldAlong == 'y')
            {
                if (dot.second > num)
                {
                    Coordinate newDot = std::make_pair(dot.first, num - (dot.second - num));
                    dots.erase(dot);
                    dots.insert(newDot); // when it already exists it does not insert, so no doubles
                }
            }
            if (foldAlong == 'x')
            {
                if (dot.first > num)
                {
                    Coordinate newDot = std::make_pair(num - (dot.first - num), dot.second);
                    dots.erase(dot);
                    dots.insert(newDot); // when it already exists it does not insert, so no doubles
                }
            }
        }
    }

    return dots;
}

int main(void)
{
    std::string testInput = "6,10\n0,14\n9,10\n0,3\n10,4\n4,11\n6,0\n6,12\n4,1\n0,13\n10,12\n3,4\n3,0\n8,4\n1,10\n2,14\n8,10\n9,0\n\nfold along y=7\nfold along x=5";
    std::set<Coordinate> testInputDots = toCoordinates(StringParser::toVector(StringParser::toVector(testInput, "\n\n")[0], "\n"));
    std::vector<std::string> testInputInstructions = StringParser::toVector(StringParser::toVector(testInput, "\n\n")[1], "\n");
    assert(executeInstructions(testInputDots, testInputInstructions, 1).size() == 17);
    
    FileHandler fileHandler("input-files/2021/day13.txt");
    std::set<Coordinate> inputDots = toCoordinates(StringParser::toVector(StringParser::toVector(fileHandler.getBuffer(), "\n\n")[0], "\n"));
    std::vector<std::string> inputInstructions = StringParser::toVector(StringParser::toVector(fileHandler.getBuffer(), "\n\n")[1], "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 1: " << std::flush << executeInstructions(inputDots, inputInstructions, 1).size() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::set<Coordinate> dots = executeInstructions(inputDots, inputInstructions, inputInstructions.size());
    std::cout << "Day 13, puzzle 2: " << std::endl;
    int maxY = 0;
    for (Coordinate dot : dots)
    {
        if (dot.second > maxY)
        {
            maxY = dot.second;
        }
    }
    for (int y = 0; y <= maxY; y++)
    {
        for (int x = 0; x <= dots.rbegin()->first; x++)
        {
            if (dots.find(std::make_pair(x,y)) != dots.end())
            {
                std::cout << "#";
            }
            else 
            {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
