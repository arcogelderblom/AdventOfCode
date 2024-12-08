#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool isInBounds(const int & x, const int & y, const std::vector<std::string> & map)
{
    return x >= 0 && x < map[y].size() && y >= 0 && y < map.size();
}

// antenna locations per frequency, saved as x,y where 0,0 is topleft most corner
std::map<char, std::vector<std::pair<int, int>>> getAntennaLocations(const std::vector<std::string> & map)
{
    std::map<char, std::vector<std::pair<int, int>>> antennaLocations; 

    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] != '.')
            {
                antennaLocations[map[y][x]].push_back(std::make_pair(x, y));
            }
        }
    }

    return antennaLocations;
}

void getAntinodeLocations(const std::pair<int, int> & node1, const std::pair<int, int> & node2, std::set<std::pair<int,int>> & antinodeLocations, const std::vector<std::string> & map)
{
    int deltaX = node1.first - node2.first;
    int deltaY = node1.second - node2.second;

    if (isInBounds(node1.first + deltaX, node1.second + deltaY, map))
    {
        antinodeLocations.insert(std::make_pair(node1.first + deltaX, node1.second + deltaY));
    }

    if (isInBounds(node2.first - deltaX, node2.second - deltaY, map))
    {
        antinodeLocations.insert(std::make_pair(node2.first - deltaX, node2.second - deltaY));
    }
}


void getAllAntinodeLocations(const std::pair<int, int> & node1, const std::pair<int, int> & node2, std::set<std::pair<int,int>> & antinodeLocations, const std::vector<std::string> & map)
{
    int deltaX = node1.first - node2.first;
    int deltaY = node1.second - node2.second;

    int x = node1.first + deltaX;
    int y = node1.second + deltaY;

    while(isInBounds(x, y, map))
    {
        antinodeLocations.insert(std::make_pair(x, y));
        x += deltaX;
        y += deltaY;
    }

    x = node2.first - deltaX;
    y = node2.second - deltaY;
    while(isInBounds(x, y, map))
    {
        antinodeLocations.insert(std::make_pair(x, y));
        x -= deltaX;
        y -= deltaY;
    }
}

int part1(const std::vector<std::string> & input) 
{
    std::set<std::pair<int, int>> antinodeLocations;
    std::map<char, std::vector<std::pair<int, int>>> antennaLocations = getAntennaLocations(input);

    for (const auto & antennaLocationsPerFrequency : antennaLocations)
    {
        for (int first = 0; first < antennaLocationsPerFrequency.second.size(); first++)
        {
            for (int second = 0; second < antennaLocationsPerFrequency.second.size(); second++)
            {
                if (second == first) { continue; }
                getAntinodeLocations(antennaLocationsPerFrequency.second[first], antennaLocationsPerFrequency.second[second], antinodeLocations, input);
            }
        }
    }

    return antinodeLocations.size();
}

int part2(const std::vector<std::string> & input) 
{
    std::set<std::pair<int, int>> antinodeLocations;
    std::map<char, std::vector<std::pair<int, int>>> antennaLocations; // antenna locations per frequency, saved as x,y where 0,0 is topleft most corner

    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            if (input[y][x] != '.')
            {
                antennaLocations[input[y][x]].push_back(std::make_pair(x, y));
            }
        }
    }

    for (const auto & antennaLocationsPerFrequency : antennaLocations)
    {
        for (int first = 0; first < antennaLocationsPerFrequency.second.size(); first++)
        {
            for (int second = 0; second < antennaLocationsPerFrequency.second.size(); second++)
            {
                if (second == first) { continue; }
                getAllAntinodeLocations(antennaLocationsPerFrequency.second[first], antennaLocationsPerFrequency.second[second], antinodeLocations, input);
            }
        }
    }

    // add all antinode locations where antenna's are located
    for (const auto & antennaLocationsPerFrequency : antennaLocations)
    {
        if (antennaLocationsPerFrequency.second.size() > 1)
        {
            for (const std::pair<int, int> location : antennaLocationsPerFrequency.second)
            antinodeLocations.insert(location);
        }
    }

    return antinodeLocations.size();
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day08_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 14);

    FileHandler fileHandler("input-files/2024/day08.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 34);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}