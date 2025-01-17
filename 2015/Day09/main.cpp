#include <iostream>
#include <cassert>

#include <set>
#include <map>
#include <algorithm>

#include "StringParser.hpp"
#include "FileHandler.hpp"



int part1(std::vector<std::string> input)
{
    int result = std::numeric_limits<int>::max();
    std::set<std::string> locations;
    std::map<std::pair<std::string, std::string>, int> distances;
    for (const std::string & line : input)
    {
        // London to Belfast = 518
        std::string first = line.substr(0, line.find_first_of(" "));
        std::string second = line.substr(line.find("to") + 3, (line.find("=") - 1) - (line.find("to") + 3));
        locations.insert(first);
        locations.insert(second);
        int distance = std::stoi(line.substr(line.find_last_of(" ")));
        distances[{ first, second }] = distance;
        distances[{ second, first }] = distance;
    }

    std::vector<std::string> current(locations.begin(), locations.end());
    do
    {
        int distance = 0;
        
        for (int i = 0; i < current.size() - 1; i++)
        {
            distance += distances[{ current[i], current[i+1] }];
        }
        
        if (distance < result)
        {
            result = distance;
        }
    } while (std::next_permutation(current.begin(), current.end()));
    
    return result;
}

int part2(std::vector<std::string> input)
{
    int result = 0;
    std::set<std::string> locations;
    std::map<std::pair<std::string, std::string>, int> distances;
    for (const std::string & line : input)
    {
        // London to Belfast = 518
        std::string first = line.substr(0, line.find_first_of(" "));
        std::string second = line.substr(line.find("to") + 3, (line.find("=") - 1) - (line.find("to") + 3));
        locations.insert(first);
        locations.insert(second);
        int distance = std::stoi(line.substr(line.find_last_of(" ")));
        distances[{ first, second }] = distance;
        distances[{ second, first }] = distance;
    }

    std::vector<std::string> current(locations.begin(), locations.end());
    do
    {
        int distance = 0;
        
        for (int i = 0; i < current.size() - 1; i++)
        {
            distance += distances[{ current[i], current[i+1] }];
        }
        
        if (distance > result)
        {
            result = distance;
        }
    } while (std::next_permutation(current.begin(), current.end()));
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2015/day09_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput) == 605);

    FileHandler fileHandler("input-files/2015/day09.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 982);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}