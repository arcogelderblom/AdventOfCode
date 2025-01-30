#include <iostream>
#include <cassert>

#include <map>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int options(const std::vector<int> & containers, const int & targetAmount, std::vector<int> used = std::vector<int>(), int eggnog = 0, int index = 0)
{
    if (eggnog == targetAmount)
    {
        return 1;
    }
    if (index == containers.size())
    {
        return 0;
    }
    int total = 0;
    while (index < containers.size())
    {
        eggnog += containers[index];
        used.push_back(containers[index]);
        total += options(containers, targetAmount, used, eggnog, index + 1);
        used.pop_back();
        eggnog -= containers[index];
        index++;
    }
    return total;
}


void options(const std::vector<int> & containers, std::vector<std::vector<int>> & allOptions, const int & targetAmount, std::vector<int> used = std::vector<int>(), int eggnog = 0, int index = 0)
{
    if (eggnog == targetAmount)
    {
        allOptions.push_back(used);
        return;
    }
    if (index == containers.size())
    {
        return;
    }
    
    while (index < containers.size())
    {
        eggnog += containers[index];
        used.push_back(containers[index]);
        options(containers, allOptions, targetAmount, used, eggnog, index + 1);
        used.pop_back();
        eggnog -= containers[index];
        index++;
    }
}

int part1(const std::vector<std::string> & input, const int & targetAmountEggnog)
{
    std::vector<int> containers;
    for (const std::string & line : input)
    {
        containers.push_back(std::stoi(line));
    }

    std::vector<std::vector<int>> allOptions;
    options(containers, allOptions, targetAmountEggnog);

    return allOptions.size();
}

int part2(const std::vector<std::string> & input, const int & targetAmountEggnog)
{ 
    std::vector<int> containers;
    for (const std::string & line : input)
    {
        containers.push_back(std::stoi(line));
    }

    std::vector<std::vector<int>> allOptions;
    options(containers, allOptions, targetAmountEggnog);

    int smallestSize = std::numeric_limits<int>::max();
    std::map<int, int> count;
    for (const std::vector<int> & option : allOptions)
    {
        count[option.size()]++;
        if (option.size() < smallestSize)
        {
            smallestSize = option.size();
        }
    }

    return count[smallestSize];
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2015/day17_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput, 25) == 4);

    FileHandler fileHandler("input-files/2015/day17.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 1: " << std::flush << part1(input, 150) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 2: " << std::flush << part2(input, 150)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}