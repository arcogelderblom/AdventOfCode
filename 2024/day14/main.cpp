#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long long part1(const std::vector<std::string> & input, const int & maxX, const int & maxY) 
{
    int result = 0;
    int quadrant1 = 0, quadrant2 = 0, quadrant3 = 0, quadrant4 = 0;
    
    for (const std::string & line : input)
    {
        int x = std::stoi(line.substr(2, line.find_first_of(',') - 2));
        int y = std::stoi(line.substr(line.find_first_of(',') + 1, line.find(' ') - line.find_first_of(',')));
        int vx = std::stoi(line.substr(line.find("v=") + 2, line.find_first_of(',') - (line.find("v=") + 2)));
        int vy = std::stoi(line.substr(line.find_last_of(',') + 1));
        
        int resultX= (x + ((vx * 100) % maxX)) % maxX;
        int resultY= (y + ((vy * 100) % maxY)) % maxY;
        if (resultX < 0)
        {
            resultX = maxX - std::abs(resultX);
        }
        if (resultY < 0)
        {
            resultY = maxY - std::abs(resultY);
        }

        bool leftSide = resultX < ((maxX - 1) / 2);
        bool rightSide = resultX > ((maxX - 1) / 2);
        bool upperSide = resultY < ((maxY - 1) / 2);
        bool lowerSide = resultY > ((maxY - 1) / 2);
        if (leftSide && upperSide)
        {
            quadrant1++;
        }
        else if (rightSide && upperSide)
        {
            quadrant2++;
        }
        else if (leftSide && lowerSide)
        {
            quadrant3++;
        }
        else if (rightSide && lowerSide)
        {
            quadrant4++;
        }
    }

    result = quadrant1 * quadrant2 * quadrant3 * quadrant4;

    return result;
}

int part2(const std::vector<std::string> & input, const int & maxX, const int & maxY) 
{
    int result = 0;
    
    for (int i = 0; i < 100000; i++)
    {
        std::set<std::pair<int, int>> robotLocations;
            
        for (const std::string & line : input)
        {
            int x = std::stoi(line.substr(2, line.find_first_of(',') - 2));
            int y = std::stoi(line.substr(line.find_first_of(',') + 1, line.find(' ') - line.find_first_of(',')));
            int vx = std::stoi(line.substr(line.find("v=") + 2, line.find_first_of(',') - (line.find("v=") + 2)));
            int vy = std::stoi(line.substr(line.find_last_of(',') + 1));
            
            int resultX= (x + ((vx * i) % maxX)) % maxX;
            int resultY= (y + ((vy * i) % maxY)) % maxY;
            if (resultX < 0)
            {
                resultX = maxX - std::abs(resultX);
            }
            if (resultY < 0)
            {
                resultY = maxY - std::abs(resultY);
            }

            auto retVal = robotLocations.insert(std::make_pair(resultX, resultY));
            if (!retVal.second) { break; } // if cannot insert then the positions are not all unique so it cannot be the 'easter egg' case
        }

        if (input.size() == robotLocations.size())
        {
            result = i;
            break;
        }
    }
    
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day14_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput, 11, 7) == 12);

    FileHandler fileHandler("input-files/2024/day14.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 1: " << std::flush << part1(input, 101, 103) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 2: " << std::flush << part2(input, 101, 103) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}