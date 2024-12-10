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

void createTree(std::pair<int, int> node, std::map<std::pair<int, int>, std::set<std::pair<int, int>>> & tree, const std::vector<std::string> & map)
{
    std::pair<int, int> directionUp = std::make_pair(0, -1);
    std::pair<int, int> directionDown = std::make_pair(0, 1);
    std::pair<int, int> directionLeft = std::make_pair(-1, 0);
    std::pair<int, int> directionRight = std::make_pair(1, 0);
    std::vector<std::pair<int, int>> directions = { directionUp, directionDown, directionLeft, directionRight };

    if (map[node.second][node.first] == '9')
    {
        return;
    }
    for (const std::pair<int, int> direction : directions)
    {
        std::pair<int, int> nextNode = std::make_pair(node.first + direction.first, node.second + direction.second);

        if (isInBounds(nextNode.first, nextNode.second, map))
        {
            if (map[nextNode.second][nextNode.first] - map[node.second][node.first] == 1)
            {
                tree[node].insert(nextNode);
                createTree(nextNode, tree, map);
            }
        }
    }
}

void getFullRoutes(const std::pair<int, int> & node, std::map<std::pair<int, int>, std::set<std::pair<int, int>>> & tree, std::vector<std::vector<std::pair<int, int>>> & allRoutes, std::vector<std::pair<int, int>> currentRoute = std::vector<std::pair<int, int>>())
{
    currentRoute.push_back(node);
    for (const std::pair<int, int> & nextNode : tree[node])
    {
        getFullRoutes(nextNode, tree, allRoutes, currentRoute);
    }

    if (currentRoute.size() == 10)
    {
        allRoutes.push_back(currentRoute);
    }
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input.size(); x++)
        {
            if (input[y][x] == '0')
            {
                std::map<std::pair<int, int>, std::set<std::pair<int, int>>> tree;
                int trailheadScore = 0;
                std::set<std::pair<int, int>> peaksReached;
                createTree(std::make_pair(x, y), tree, input);
                for (const auto node : tree)
                {
                    if (input[node.first.second][node.first.first] == '8')
                    {
                        peaksReached.insert(node.second.begin(), node.second.end());
                    }
                }
                result += peaksReached.size();
            }
        }
    }
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
     for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input.size(); x++)
        {
            if (input[y][x] == '0')
            {
                std::map<std::pair<int, int>, std::set<std::pair<int, int>>> tree;
                int trailheadScore = 0;
                std::set<std::pair<int, int>> peaksReached;
                createTree(std::make_pair(x, y), tree, input);
                std::vector<std::vector<std::pair<int, int>>> allRoutes;
                getFullRoutes(std::make_pair(x, y), tree, allRoutes);
                result += allRoutes.size();
            }
        }
    }
    return result;
}

int main(void) 
{    
    FileHandler testFileHandler("input-files/2024/day10_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 36);
    
    FileHandler fileHandler("input-files/2024/day10.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 81);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}