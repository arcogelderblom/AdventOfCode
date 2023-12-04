#include <iostream>
#include <cassert>
#include <chrono>

#include <map>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int part1(const std::vector<std::string> & input) 
{
    std::map<std::string, int> validCubeAmounts = { {"red", 12}, {"green", 13} , {"blue", 14} };

    int result = 0;
    for (int i = 0; i < input.size(); i++)
    {
        int gameId = i + 1;
        std::string gameRecord = input[i].substr(std::string("Game : ").size() + std::to_string(gameId).size());
        std::vector<std::string> parsedGameRecord = StringParser::toVector(gameRecord, "; ");
        bool validGame = true;
        for (const std::string & subset : parsedGameRecord)
        {
            std::vector<std::string> cubes = StringParser::toVector(subset, ", ");
            for (const std::string & cube : cubes)
            {
                std::vector<std::string> parsedCube = StringParser::toVector(cube, " ");
                int amount = std::stoi(parsedCube[0]);
                if (amount > validCubeAmounts[parsedCube[1]])
                {
                    validGame = false;
                    break;
                }
            }
            if (!validGame)
            {
                break;
            }
        }
        if (validGame)
        {
            result += gameId;
        }
    }
    return result;
}

long part2(const std::vector<std::string> & input) 
{
    long result = 0;
    for (int i = 0; i < input.size(); i++)
    {
        int gameId = i + 1;
        std::string gameRecord = input[i].substr(std::string("Game : ").size() + std::to_string(gameId).size());
        std::vector<std::string> parsedGameRecord = StringParser::toVector(gameRecord, "; ");
        
        std::map<std::string, int> minimumAmountCubes = { {"red", 0}, {"green", 0} , {"blue", 0} };
        for (const std::string & subset : parsedGameRecord)
        {
            std::vector<std::string> cubes = StringParser::toVector(subset, ", ");
            for (const std::string & cube : cubes)
            {
                std::vector<std::string> parsedCube = StringParser::toVector(cube, " ");
                int amount = std::stoi(parsedCube[0]);
                if (amount > minimumAmountCubes[parsedCube[1]])
                {
                    minimumAmountCubes[parsedCube[1]] = amount;
                }
            }
        }
        result += (minimumAmountCubes["red"] * minimumAmountCubes["green"] * minimumAmountCubes["blue"]);
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day02_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 8);

    FileHandler fileHandler("input-files/2023/day02.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 2286);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}