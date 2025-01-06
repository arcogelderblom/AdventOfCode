#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <set>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool isInBounds(const std::pair<int, int> & coordinate, const int & maxX, const int & maxY)
{
    return coordinate.first >= 0 && coordinate.first <= maxX && coordinate.second >= 0 && coordinate.second <= maxY;
}

int distanceTo(const std::pair<int, int> & first, const std::pair<int, int> & second)
{
    return std::abs(first.first - second.first) + std::abs(first.second - second.second);
}

int getPicoSecondsForShortestPath(std::pair<int, int> & start, const std::pair<int, int> & finish, const std::vector<std::string> & map, std::map<std::pair<int, int>, int> & picosecondsToCoordinate)
{
    // pair consists of <current steps + min steps to end, current coordinate>
    std::set<std::pair<int, std::pair<int, int>>> next = { { 0 + distanceTo(start, finish), { start } } }; 
    std::vector<std::pair<int, int>> directions = { { 0, -1 }, // up
                                                    { 0, 1 },  // down
                                                    { -1, 0 }, // left
                                                    { 1, 0 } };// right
    std::set<std::pair<int, int>> visited = { start };
    std::pair<int, std::pair<int, int>> current = *next.begin();
    next.erase(current);
    picosecondsToCoordinate[current.second] = current.first - distanceTo(current.second, finish);

    while (current.second != finish)
    {
        for (const std::pair<int, int> & d : directions)
        {
            std::pair<int, int> nextCoordinate = std::make_pair(current.second.first + d.first, current.second.second + d.second);
            if (map[nextCoordinate.second][nextCoordinate.first] != '#' && isInBounds(nextCoordinate, map[map.size() - 1].size() - 1, map.size() - 1) && visited.find(nextCoordinate) == visited.end())
            {
                picosecondsToCoordinate[nextCoordinate] = current.first + 1 - distanceTo(current.second, finish);
                next.insert(std::make_pair(current.first + 1 - distanceTo(current.second, finish) + distanceTo(nextCoordinate, finish), nextCoordinate));
                visited.insert(nextCoordinate);
            }
        }
        if (next.size() > 0)
        {
            current = *next.begin();
            next.erase(current);
        }
    }
    
    return current.first;
}

std::pair<int, int> find(const char & c, const std::vector<std::string> & map)
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == c) { return { x, y }; }
        }
    }
    return { -1, -1};
}

void calculatePicosecondsShortcut(const std::pair<int, int> & current, std::vector<std::pair<int, int>> shortcuts, std::map<std::pair<int, int>, int> & picosecondsToCoordinate, std::map<std::set<std::pair<int, int>>, int> & shortcutsWithPicosecondsSaved)
{
    int maxPicoseconds = 0;
    std::set<std::pair<int, int>> shortcut;
    for (int i = 0; i < shortcuts.size(); i++)
    {
        std::pair<int, int> next = {current.first + shortcuts[i].first, current.second + shortcuts[i].second};
        if (picosecondsToCoordinate.find(current) != picosecondsToCoordinate.end() && 
            picosecondsToCoordinate.find(next) != picosecondsToCoordinate.end())
        {
            int shortcutSeconds = std::abs(picosecondsToCoordinate[current] - picosecondsToCoordinate[next]) - ((std::abs(shortcuts[i].first)) + (std::abs(shortcuts[i].second)));
            if (shortcutSeconds > 0)
            {
                shortcut = { current, next };
                shortcutsWithPicosecondsSaved[shortcut] = shortcutSeconds;
            }
        }
    }
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<std::string> map = input;
    std::pair<int, int> start = find('S', map);
    std::pair<int, int> end = find('E', map);
    std::map<std::pair<int, int>, int> picosecondsToCoordinate;

    std::vector<std::pair<int, int>> shortcuts = { { 0, -2 },
                                                   { 1, -1 },
                                                   { 2, 0 }, 
                                                   { 1, 1 }, 
                                                   { 0, 2 }, 
                                                   { -1, 1 },  
                                                   { -2, 0 }, 
                                                   { -1, -1 } };

    int picoseconds = getPicoSecondsForShortestPath(start, end, map, picosecondsToCoordinate);
    std::map<std::set<std::pair<int, int>>, int> shortcutsWithPicosecondsSaved;
    for (int y = 0; y <= map.size(); y++)
    {
        for (int x = 0; x <= map[y].size(); x++)
        {
            calculatePicosecondsShortcut({x, y}, shortcuts, picosecondsToCoordinate, shortcutsWithPicosecondsSaved);
        }
    }

    for (const std::pair<std::set<std::pair<int, int>>, int> & shortcutAndPicosecondsSaved : shortcutsWithPicosecondsSaved)
    {
        if (shortcutAndPicosecondsSaved.second >= 100)
        {
            result++;
        }
    }

    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<std::string> map = input;
    std::pair<int, int> start = find('S', map);
    std::pair<int, int> end = find('E', map);
    std::map<std::pair<int, int>, int> picosecondsToCoordinate;

    // generate all shortcut endpoints
    std::vector<std::pair<int, int>> shortcuts;
    for (int shortcutTime = 2; shortcutTime <= 20; shortcutTime++)
    {
        for (int i = shortcutTime * -1; i <= shortcutTime; i++)
        {
            int j = std::abs(i) - shortcutTime;
            shortcuts.push_back({i , j});
            j*=-1;
            if (j != 0)
            {
                shortcuts.push_back({i , j});
                j*=-1;
            }
            j++;
        }
    }
   
    int picoseconds = getPicoSecondsForShortestPath(start, end, map, picosecondsToCoordinate);
    
    std::map<std::set<std::pair<int, int>>, int> shortcutsWithPicosecondsSaved;
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] != '#')
            {
                calculatePicosecondsShortcut({x, y}, shortcuts, picosecondsToCoordinate, shortcutsWithPicosecondsSaved);
            }
        }
    }

    for (const std::pair<std::set<std::pair<int, int>>, int> & shortcutAndPicosecondsSaved : shortcutsWithPicosecondsSaved)
    {
        if (shortcutAndPicosecondsSaved.second >= 100)
        {
            result++;
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day20_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    
    FileHandler fileHandler("input-files/2024/day20.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}