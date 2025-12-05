#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include <set>

int part1(const std::vector<std::string> & input)
{
    int result = 0;
    
    std::vector<std::string> rangesStrs = StringParser::toVector(input[0], "\n");
    std::set<std::pair<long long, long long>> ranges;
    for (const std::string & range : rangesStrs)
    {
        std::vector<long long> splitted = StringParser::toLongLongVector(range, "-");
        ranges.insert({splitted[0], splitted[1]});
    }

    std::vector<std::string> ids = StringParser::toVector(input[1], "\n");
    for (const std::string & idStr : ids)
    {
        long long id = std::stoll(idStr);
        for (std::pair<long long, long long> range : ranges)
        {
            if (range.first <= id && range.second >= id)
            {
                result++;
                break;
            }
            if (range.first > id)
            {
                break; // ingredient is spoiled, stop processing
            }
        }
    }

    return result;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0; 

    std::vector<std::string> rangesStrs = StringParser::toVector(input[0], "\n");
    std::set<std::pair<long long, long long>> ranges;
    for (const std::string & range : rangesStrs)
    {
        std::vector<long long> splitted = StringParser::toLongLongVector(range, "-");
        ranges.insert({splitted[0], splitted[1]});
    }

    std::set<std::pair<long long, long long>> combinedRanges;
    combinedRanges.insert(*ranges.begin());
    for (auto it = ++ranges.begin(); it != ranges.end(); it++)
    {
        std::pair<long long, long long> compareTo = *(combinedRanges.rbegin());
        if ((*it).first >= compareTo.first && (*it).first <= compareTo.second && (*it).second > compareTo.second) // starts within range, ends later
        {
            combinedRanges.erase(compareTo);
            combinedRanges.insert({compareTo.first, (*it).second});
        }
        else if ((*it).first < compareTo.first && (*it).second >= compareTo.first && (*it).second <= compareTo.second) // starts before range ends within
        {
            combinedRanges.erase(compareTo);
            combinedRanges.insert({(*it).first, compareTo.second});
        }
        else if ((*it).first < compareTo.first && (*it).second > compareTo.second) // starts before range and ends after
        {
            combinedRanges.erase(compareTo);
            combinedRanges.insert({(*it).first, (*it).second});
        }
        else if ((*it).first >= compareTo.first && (*it).first <= compareTo.second && (*it).second >= compareTo.first && (*it).second <= compareTo.second) // is already within existing range
        {
            continue;
        }
        else // no intersection, add
        {
            combinedRanges.insert(*it);
        }
    }

    for (std::pair<long long, long long> range : combinedRanges)
    {
        result += range.second - range.first + 1;
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day05_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");
    assert(part1(testinput) == 3);

    FileHandler fileHandler("input-files/2025/day05.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 14);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}