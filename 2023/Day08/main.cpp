#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <algorithm>
#include <map>
#include <numeric>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::map<std::string, std::pair<std::string, std::string>> nodeAndNextElems;
    std::string instructions = input[0];
    for (const std::string & line : StringParser::toVector(input[1], "\n"))
    {
        // all entries are same in length and indexes
        std::string node = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);
        nodeAndNextElems[node] = std::make_pair(left, right);
    }

    int i = 0;
    std::string currentNode = "AAA";
    while (currentNode != "ZZZ")
    {
        if (instructions[i] == 'L')
        {
            currentNode = nodeAndNextElems[currentNode].first;
        }
        else if (instructions[i] == 'R')
        {
            currentNode = nodeAndNextElems[currentNode].second;
        }
        result++;
        i++;
        if (i == (instructions.size()))
        {
            i = 0;
        }
    }
    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::map<std::string, std::pair<std::string, std::string>> nodeAndNextElems;
    std::vector<std::string> startNodes;
    std::string instructions = input[0];
    for (const std::string & line : StringParser::toVector(input[1], "\n"))
    {
        // all entries are same in length and indexes
        std::string node = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);
        nodeAndNextElems[node] = std::make_pair(left, right);
        if (node[2] == 'A')
        {
            startNodes.push_back(node);
        }
    }


    std::vector<int> allSteps;
    for (const std::string & startNode : startNodes)
    {
        int i = 0;
        int steps = 0;
        std::string currentNode = startNode;
        while (currentNode[2] != 'Z')
        {
            if (instructions[i] == 'L')
            {
                currentNode = nodeAndNextElems[currentNode].first;
            }
            else if (instructions[i] == 'R')
            {
                currentNode = nodeAndNextElems[currentNode].second;
            }
            steps++;
            i++;
            if (i == (instructions.size()))
            {
                i = 0;
            }
        }
        allSteps.push_back(steps);
    }

    long long currentLeastCommonMultiple = std::lcm(allSteps[0], allSteps[1]);
    for (int i = 2; i < allSteps.size(); i++)
    {
        currentLeastCommonMultiple = std::lcm(currentLeastCommonMultiple, allSteps[i]);
    }
    result = currentLeastCommonMultiple;
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day08_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n\n");
    FileHandler fileHandlerTest2("input-files/2023/day08_testinput2.txt");
    std::vector<std::string> testInput2 = StringParser::toVector(fileHandlerTest2.getBuffer(), "\n\n");
    assert(part1(testInput) == 2);
    assert(part1(testInput2) == 6);

    FileHandler fileHandler("input-files/2023/day08.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    FileHandler fileHandlerTest3("input-files/2023/day08_testinput3.txt");
    std::vector<std::string> testInput3 = StringParser::toVector(fileHandlerTest3.getBuffer(), "\n\n");
    assert(part2(testInput3) == 6);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}