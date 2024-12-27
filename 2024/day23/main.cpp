#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>
#include <algorithm>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::map<std::string, std::vector<std::string>> computers;
    for (const std::string & line : input)
    {
        std::string first = line.substr(0, 2);
        std::string second = line.substr(3);
        computers[first].push_back(second);
        computers[second].push_back(first);
    }
    
    std::set<std::set<std::string>> threeInterConnected;
    for (const std::pair<std::string, std::vector<std::string>> & connections : computers)
    {
        if (connections.second.size() >= 2)
        {
            for (int a = 0; a < connections.second.size(); a++)
            {
                for (int b = a; b < connections.second.size(); b++)
                {
                    if (std::find(computers[connections.second[a]].begin(), computers[connections.second[a]].end(), connections.second[b]) != computers[connections.second[a]].end())
                    {
                        threeInterConnected.insert({ connections.first, connections.second[a], connections.second[b] });
                    }
                }    
            }
        }
    }

    for (const std::set<std::string> & entry : threeInterConnected)
    {
        if (std::find_if(entry.begin(), entry.end(), [](const std::string & str){ return str.starts_with('t'); }) != entry.end())
        {
            result++;
        }
    }

    return result;
}

std::string part2(const std::vector<std::string> & input) 
{
    std::string result;
    
    std::map<std::string, std::vector<std::string>> computers;
    for (const std::string & line : input)
    {
        std::string first = line.substr(0, 2);
        std::string second = line.substr(3);
        computers[first].push_back(second);
        computers[second].push_back(first);
    }
    
    std::set<std::set<std::string>> interconnectedComputers;
    for (const std::pair<std::string, std::vector<std::string>> & connections : computers)
    {
        if (connections.second.size() >= 2)
        {
            for (int a = 0; a < connections.second.size(); a++)
            {
                std::set<std::string> interconnected;
                interconnected.insert(connections.first);
                interconnected.insert(connections.second[a]);
                for (int b = 0; b < connections.second.size(); b++)
                {
                    if (b == a) { continue; }
                    bool allComputersInterconnected = true;
                    for (const std::string & computer : interconnected)
                    {
                        if (std::find(computers[computer].begin(), computers[computer].end(), connections.second[b]) == computers[computer].end())
                        {
                            allComputersInterconnected = false;
                        }
                    }
                    if (allComputersInterconnected)
                    {
                        interconnected.insert(connections.second[b]);
                    }
                }
                interconnectedComputers.insert(interconnected);
            }
        }
    }

    int largest = 0;
    for (const auto & interconnected : interconnectedComputers)
    {
        if (interconnected.size() > largest)
        {
            largest = interconnected.size();
            result = "";
            for (const auto & str : interconnected)
            {
                result += str + ',';
            }

        }
    }

    return result.substr(0, result.size() - 1);
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day23_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput) == 7);

    FileHandler fileHandler("input-files/2024/day23.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 23, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == "co,de,ka,ta");

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 23, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}