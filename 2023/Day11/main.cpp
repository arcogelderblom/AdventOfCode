#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <utility>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

std::vector<std::string> expand(const std::vector<std::string> & src, int times = 2)
{
    std::vector<std::string> result;
    
    // find rows that need to be expanded
    for (const std::string & line : src)
    {
        if (line.find('#') == std::string::npos)
        {
            for (int time = 1; time <= times; time++)
            {
                result.push_back(line);
            }
        }
        else
        {
            result.push_back(line);
        }
    }

    // find columns that need to be expanded
    for (int i = 0; i < result[0].size(); i++)
    {
        bool galaxyFound = false;
        for (const std::string & line : result)
        {
            if (line[i] == '#')
            {
                galaxyFound = true;
                break;
            }
        }

        if (!galaxyFound)
        {
            for (std::string & line : result)
            {
                // one time less since we already have a complete row with no galaxies and we are only adding
                for (int time = 2; time <= times; time++)
                {
                    line.insert(i + 1, ".");
                }
            }
            i += times + 1;
        }
    }

    return result;
}

long long getSumDistances(const std::vector<std::string> & image)
{
    long long result = 0;

    std::vector<Coordinate> galaxies;
    for (int y = 0; y < image.size(); y++)
    {
        for (int x = 0; x < image[y].size(); x++)
        {
            if (image[y][x] == '#')
            {
                galaxies.push_back(std::make_pair(x, y));
            }
        }
    }

    for (int i = 0; i < galaxies.size(); i++)
    {
        for (int j = i + 1; j < galaxies.size(); j++)
        {
            result += std::abs(galaxies[i].first - galaxies[j].first) + std::abs(galaxies[i].second - galaxies[j].second);
        }
    }
    return result;
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    
    std::vector<std::string> image = expand(input);
    result = getSumDistances(image);

    return result;
}

long long part2(const std::vector<std::string> & input, int times) 
{
    long long result = 0;
    
    if (times < 20)
    {
        std::vector<std::string> image = expand(input, times);
        result = getSumDistances(image);
    }
    else 
    {
        std::vector<std::string> image = expand(input, 10);
        long long timesTen = getSumDistances(image);


        image = expand(input, 20);
        long long timesTwenty = getSumDistances(image);
        result = timesTen + ((timesTwenty - timesTen) * ((times - 10) / 10));
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day11_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 374);

    FileHandler fileHandler("input-files/2023/day11.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    assert(part2(testInput, 10) == 1030);
    assert(part2(testInput, 100) == 8410);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 2: " << std::flush << part2(input, 1000000) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}