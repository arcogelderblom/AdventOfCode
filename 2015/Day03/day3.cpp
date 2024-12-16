#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <set>

#include "StringParser.hpp"
#include "FileHandler.hpp"

typedef std::pair<int, int> Coordinate; // x,y

std::set<Coordinate> deliverPresents(std::string instructions)
{
    Coordinate currentHouse = std::make_pair(0,0);
    std::set<Coordinate> houseCoordinates = { currentHouse };
    for (char c : instructions)
    {
        if (c == '^')
        {
            currentHouse.second += 1;
        }
        else if (c == '>')
        {
            currentHouse.first += 1;
        }
        else if (c == '<')
        {
            currentHouse.first -= 1;
        }
        else if (c == 'v')
        {
            currentHouse.second -= 1;
        }
        houseCoordinates.insert(currentHouse);
    }
    return houseCoordinates;
}


std::set<Coordinate> deliverPresentsWithRoboSanta(std::string instructions)
{
    Coordinate currentHouseSanta = std::make_pair(0,0);
    Coordinate currentHouseRoboSanta = std::make_pair(0,0);
    std::set<Coordinate> houseCoordinates = { currentHouseSanta, currentHouseRoboSanta }; // add twice since RoboSanta and santa both deliver here
    bool santa = true; // santa starts, if false -> RoboSanta
    for (char c : instructions)
    {
        Coordinate* currentHouse = santa ? &currentHouseSanta : &currentHouseRoboSanta;
        if (c == '^')
        {
            currentHouse->second += 1;
        }
        else if (c == '>')
        {
            currentHouse->first += 1;
        }
        else if (c == '<')
        {
            currentHouse->first -= 1;
        }
        else if (c == 'v')
        {
            currentHouse->second -= 1;
        }
        houseCoordinates.insert(*currentHouse);
        santa = !santa;
    }
    return houseCoordinates;
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day03.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 1: " << std::flush << deliverPresents(input[0]).size() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 2: " << std::flush << deliverPresentsWithRoboSanta(input[0]).size() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}