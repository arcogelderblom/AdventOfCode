#include <iostream>
#include <cassert>

#include <map>

#include "StringParser.hpp"
#include "FileHandler.hpp"

std::string slice(const std::string & str, const std::string & before, const std::string & after)
{
    return str.substr(str.find(before) + before.size(), str.find_first_of(after, str.find(before) + before.size()));
}

int part1(std::vector<std::string> input)
{
    int result = 0;

    // expected sue:
    //      children: 3
    //      cats: 7
    //      samoyeds: 2
    //      pomeranians: 3
    //      akitas: 0
    //      vizslas: 0
    //      goldfish: 5
    //      trees: 3
    //      cars: 2
    //      perfumes: 1

    for (int sue = 1; sue <= input.size(); sue++)
    {
        if (input[sue-1].find("children") != std::string::npos)
        {
            if (std::stoi(slice(input[sue-1], "children: ", ",")) != 3)
            {
                continue;
            }
        }
        if (input[sue-1].find("cats") != std::string::npos)
        {
           if (std::stoi(slice(input[sue-1], "cats: ", ",")) != 7)
            {
                continue;
            }
        }
        if (input[sue-1].find("samoyeds") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "samoyeds: ", ",")) != 2)
            {
                continue;
            }
        }
        if (input[sue-1].find("pomeranians") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "pomeranians: ", ",")) != 3)
            {
                continue;
            }
        }
        if (input[sue-1].find("akitas") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "akitas: ", ",")) != 0)
            {
                continue;
            }
        }
        if (input[sue-1].find("vizslas") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "vizslas: ", ",")) != 0)
            {
                continue;
            }
        }
        if (input[sue-1].find("goldfish") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "goldfish: ", ",")) != 5)
            {
                continue;
            }
        }
        if (input[sue-1].find("trees") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "trees: ", ",")) != 3)
            {
                continue;
            }
        }
        if (input[sue-1].find("cars") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "cars: ", ",")) != 2)
            {
                continue;
            }
        }
        if (input[sue-1].find("perfumes") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "perfumes: ", ",")) != 1)
            {
                continue;
            }
        }
        result = sue;
    }

    return result;
}

int part2(std::vector<std::string> input)
{ 
    int result = 0;

    // expected sue:
    //      children: 3
    //      cats: >7
    //      samoyeds: 2
    //      pomeranians: <3
    //      akitas: 0
    //      vizslas: 0
    //      goldfish: <5
    //      trees: >3
    //      cars: 2
    //      perfumes: 1

    for (int sue = 1; sue <= input.size(); sue++)
    {
        if (input[sue-1].find("children") != std::string::npos)
        {
            if (std::stoi(slice(input[sue-1], "children: ", ",")) != 3)
            {
                continue;
            }
        }
        if (input[sue-1].find("cats") != std::string::npos)
        {
           if (std::stoi(slice(input[sue-1], "cats: ", ",")) <= 7)
            {
                continue;
            }
        }
        if (input[sue-1].find("samoyeds") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "samoyeds: ", ",")) != 2)
            {
                continue;
            }
        }
        if (input[sue-1].find("pomeranians") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "pomeranians: ", ",")) >= 3)
            {
                continue;
            }
        }
        if (input[sue-1].find("akitas") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "akitas: ", ",")) != 0)
            {
                continue;
            }
        }
        if (input[sue-1].find("vizslas") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "vizslas: ", ",")) != 0)
            {
                continue;
            }
        }
        if (input[sue-1].find("goldfish") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "goldfish: ", ",")) >= 5)
            {
                continue;
            }
        }
        if (input[sue-1].find("trees") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "trees: ", ",")) <= 3)
            {
                continue;
            }
        }
        if (input[sue-1].find("cars") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "cars: ", ",")) != 2)
            {
                continue;
            }
        }
        if (input[sue-1].find("perfumes") != std::string::npos)
        { 
            if (std::stoi(slice(input[sue-1], "perfumes: ", ",")) != 1)
            {
                continue;
            }
        }
        result = sue;
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandler("input-files/2015/day16.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}