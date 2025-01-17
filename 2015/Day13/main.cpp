#include <iostream>
#include <cassert>

#include <set>
#include <map>
#include <algorithm>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int getOptimalHappiness(const std::set<std::string> & persons, std::map<std::pair<std::string, std::string>, int> happinessDiff)
{
    int optimalHappiness = 0;
    std::vector<std::string> arrangement(persons.begin(), persons.end());
    do
    {
        int currentHappiness = 0;
        for (int i = 0; i < arrangement.size(); i++)
        {
            if (i == arrangement.size() - 1)
            {
                currentHappiness += happinessDiff[{ arrangement[i], arrangement[0] }];
                currentHappiness += happinessDiff[{ arrangement[0], arrangement[i] }];
            }
            else
            {
                currentHappiness += happinessDiff[{ arrangement[i], arrangement[i+1] }];
                currentHappiness += happinessDiff[{ arrangement[i+1], arrangement[i] }];
            }
        }
        if (currentHappiness > optimalHappiness)
        {
            optimalHappiness = currentHappiness;
        }
    } while (std::next_permutation(arrangement.begin(), arrangement.end()));
    return optimalHappiness;
}

int part1(std::vector<std::string> input)
{
    int result = 0;
    std::set<std::string> persons;
    std::map<std::pair<std::string, std::string>, int> happinessDiff;
    for (const std::string & line : input)
    {
        //Alice would gain 54 happiness units by sitting next to Bob.
        std::string first = line.substr(0, line.find_first_of(" "));
        std::string second = line.substr(line.find_last_of(" ") + 1, (line.size() - 1) - line.find_last_of(" ") - 1);
        bool gain = line.find("gain") != std::string::npos;
        int happiness = std::stoi(line.substr(line.find_first_of("0123456789"), line.find_first_not_of("0123456789") - line.find_first_of("0123456789")));
        persons.insert(first);
        persons.insert(second);
        happinessDiff[{ first, second }] = happiness * (gain ? 1 : -1);
    }
    
    result = getOptimalHappiness(persons, happinessDiff);

    return result;
}

int part2(std::vector<std::string> input)
{
    int result = 0;
    std::set<std::string> persons;
    std::map<std::pair<std::string, std::string>, int> happinessDiff;
    for (const std::string & line : input)
    {
        //Alice would gain 54 happiness units by sitting next to Bob.
        std::string first = line.substr(0, line.find_first_of(" "));
        std::string second = line.substr(line.find_last_of(" ") + 1, (line.size() - 1) - line.find_last_of(" ") - 1);
        bool gain = line.find("gain") != std::string::npos;
        int happiness = std::stoi(line.substr(line.find_first_of("0123456789"), line.find_first_not_of("0123456789") - line.find_first_of("0123456789")));
        persons.insert(first);
        persons.insert(second);
        happinessDiff[{ first, second }] = happiness * (gain ? 1 : -1);
    }

    for (const std::string & person : persons)
    {
        happinessDiff[ { person, "me" } ] = 0;
        happinessDiff[ { "me", person } ] = 0;
    }
    persons.insert("me");


    result = getOptimalHappiness(persons, happinessDiff);
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2015/day13_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput) == 330);

    FileHandler fileHandler("input-files/2015/day13.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}