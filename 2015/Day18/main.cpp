#include <iostream>
#include <cassert>

#include "StringParser.hpp"
#include "FileHandler.hpp"

void turnCornersOn(std::vector<std::vector<bool>> & grid)
{
    grid[0][0] = true;
    grid[grid[0].size()-1][0] = true;
    grid[0][grid.size()-1] = true;
    grid[grid[grid.size() - 1].size() - 1][grid.size()-1] = true;
}

std::vector<std::vector<bool>> next(const std::vector<std::vector<bool>> & current, bool part2 = false) 
{
    std::vector<std::pair<int, int>> directions = { { -1, -1 }, 
                                                    { 0, -1 }, 
                                                    { 1, -1 }, 
                                                    { -1, 0 },
                                                    { 1, 0 }, 
                                                    { -1, 1 }, 
                                                    { 0, 1 }, 
                                                    { 1, 1 } };
    std::vector<std::vector<bool>> future(current.size(), std::vector<bool>(current[0].size(), false));
    for (int y = 0; y < current.size(); y++)
    {
        for (int x = 0; x < current[y].size(); x++)
        {
            int neighboursOn = 0;
            for (const std::pair<int, int> & direction : directions)
            {
                if (x + direction.first >= 0 && x + direction.first < current[y].size() && y + direction.second >= 0 && y + direction.second < current.size() && current[x + direction.first][y + direction.second])
                {
                    neighboursOn++;
                }
            }
            if (current[x][y] && (neighboursOn == 2 || neighboursOn == 3))
            {
                future[x][y] = true;
            }
            else if (!current[x][y] && neighboursOn == 3)
            {
                future[x][y] = true;
            }
        }
    }
    if (part2)
    {
        turnCornersOn(future);
    }
    return future;
}

int part1(std::vector<std::string> input)
{
    int result = 0;
    std::vector<std::vector<bool>> lights(input.size(), std::vector<bool>(input[0].size(), false));
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            if (input[y][x] == '#')
            {
                lights[x][y] = true;
            }
        }
    }
    for (int step = 0; step < 100; step++)
    {
        lights = next(lights);
    }

    int amountLightsOn = 0;
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            if (lights[x][y])
            {
                amountLightsOn++;
            }
        }
    }
    result = amountLightsOn;
    return result;
}

int part2(std::vector<std::string> input)
{ 
    int result = 0;
    std::vector<std::vector<bool>> lights(input.size(), std::vector<bool>(input[0].size(), false));
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            if (input[y][x] == '#')
            {
                lights[x][y] = true;
            }
        }
    }
    turnCornersOn(lights);
    for (int step = 0; step < 100; step++)
    {
        lights = next(lights, true);
    }

    int amountLightsOn = 0;
    for (int y = 0; y < input.size(); y++)
    {
        for (int x = 0; x < input[y].size(); x++)
        {
            if (lights[x][y])
            {
                amountLightsOn++;
            }
        }
    }
    result = amountLightsOn;
    return result;
}

int main(void) 
{
    FileHandler fileHandler("input-files/2015/day18.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}