#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include <set>
#include <algorithm>
#include <iomanip>

typedef std::tuple<double, double, double> Coordinate3D;

double getDistance(Coordinate3D a, Coordinate3D b)
{
   return sqrt(pow(std::get<0>(a) - std::get<0>(b), 2) + pow(std::get<1>(a) - std::get<1>(b), 2) + pow(std::get<2>(a) - std::get<2>(b), 2));
}

int findInCircuit(Coordinate3D a, std::vector<std::set<Coordinate3D>> circuits)
{
    for (int i = 0; i < circuits.size(); i++)
    {
        if (circuits[i].find(a) != circuits[i].end())
        {
            return i;
        }
    }
    return -1;
}

void printCircuits(std::vector<std::set<Coordinate3D>> circuits)
{
    for (const std::set<Coordinate3D> & circuit : circuits)
    {
        std::cout << "Circuit contents:" << std::endl;
        std::cout << "\t";
        for (const Coordinate3D & coordinate : circuit)
        {
            std::cout << "(" << std::get<0>(coordinate) << "," << std::get<1>(coordinate) << "," << std::get<2>(coordinate) << ") -- "; 
        }
        std::cout << std::endl;
    }
}

void printMap(std::set<std::pair<double, std::pair<Coordinate3D, Coordinate3D>>> distanceAndPair)
{
    for (const auto & a : distanceAndPair)
    {
        std::cout << "Distance = " << a.first << " | (" << std::get<0>(a.second.first) << "," << std::get<1>(a.second.first) << "," << std::get<2>(a.second.first) << ") <-> (" << std::get<0>(a.second.second) << "," << std::get<1>(a.second.second) << "," << std::get<2>(a.second.second) << ")" << std::endl;   
    }
}

int part1(const std::vector<std::string> & input, int closestAmount = 1000)
{
    int result = 0;
    std::vector<Coordinate3D> coordinates;
    for (const std::string & line : input)
    {
        std::vector<int> coordinateVec = StringParser::toIntVector(line, ",");
        coordinates.push_back({coordinateVec[0], coordinateVec[1], coordinateVec[2]});
    }

    std::set<std::pair<double, std::pair<Coordinate3D, Coordinate3D>>> distanceAndPair;
    for (int i = 0; i < coordinates.size(); i++)
    {
        for (int j = 0; j < coordinates.size(); j++)
        {
            if (j == i)
            {
                j++;
                continue;
            }
            if (distanceAndPair.find({getDistance(coordinates[i], coordinates[j]), {coordinates[j], coordinates[i]}}) == distanceAndPair.end())
            {
                distanceAndPair.insert({getDistance(coordinates[i], coordinates[j]), {coordinates[i], coordinates[j]}});
            }
        }
    }

    int amount = 0;
    std::vector<std::set<Coordinate3D>> circuits;
    for (const auto & a : distanceAndPair)
    {
        int indexFirst = findInCircuit(a.second.first, circuits);
        int indexSecond = findInCircuit(a.second.second, circuits);
        if (indexFirst == -1 && indexSecond == -1) // not found in any circuit
        {
            std::set<Coordinate3D> newCircuit = {a.second.first, a.second.second};
            circuits.push_back(newCircuit);
        }
        else if (indexFirst == -1 && indexSecond != -1)
        {
            circuits[indexSecond].insert(a.second.first);
        }
        else if (indexFirst != -1 && indexSecond == -1)
        {
            circuits[indexFirst].insert(a.second.second);
        }
        else if (indexFirst != -1 && indexSecond != -1 && indexFirst != indexSecond)
        {
            circuits[indexFirst].insert(circuits[indexSecond].begin(), circuits[indexSecond].end());
            circuits.erase(circuits.begin() + indexSecond);
        }

        amount++;
        if (amount == closestAmount)
        {
            break;
        }
    }
    
    assert(circuits.size() >= 3);
    std::sort(circuits.begin(), circuits.end(), [](const std::set<Coordinate3D> & a, const std::set<Coordinate3D> & b){ return a.size() > b.size(); });
    return circuits[0].size() * circuits[1].size() * circuits[2].size();
}

double part2(const std::vector<std::string> & input) 
{
    double result = 0;
    std::vector<Coordinate3D> coordinates;
    for (const std::string & line : input)
    {
        std::vector<int> coordinateVec = StringParser::toIntVector(line, ",");
        coordinates.push_back({coordinateVec[0], coordinateVec[1], coordinateVec[2]});
    }

    std::set<std::pair<double, std::pair<Coordinate3D, Coordinate3D>>> distanceAndPair;
    for (int i = 0; i < coordinates.size(); i++)
    {
        for (int j = 0; j < coordinates.size(); j++)
        {
            if (j == i)
            {
                j++;
                continue;
            }
            if (distanceAndPair.find({getDistance(coordinates[i], coordinates[j]), {coordinates[j], coordinates[i]}}) == distanceAndPair.end())
            {
                distanceAndPair.insert({getDistance(coordinates[i], coordinates[j]), {coordinates[i], coordinates[j]}});
            }
        }
    }
    
    std::vector<std::set<Coordinate3D>> circuits;
    std::set<Coordinate3D> coordinatesInCircuit;
    for (const auto & a : distanceAndPair)
    {
        int indexFirst = findInCircuit(a.second.first, circuits);
        int indexSecond = findInCircuit(a.second.second, circuits);
        coordinatesInCircuit.insert(a.second.first);
        coordinatesInCircuit.insert(a.second.second);
        if (indexFirst == -1 && indexSecond == -1) // not found in any circuit
        {
            std::set<Coordinate3D> newCircuit = {a.second.first, a.second.second};
            circuits.push_back(newCircuit);
        }
        else if (indexFirst == -1 && indexSecond != -1)
        {
            circuits[indexSecond].insert(a.second.first);
        }
        else if (indexFirst != -1 && indexSecond == -1)
        {
            circuits[indexFirst].insert(a.second.second);
        }
        else if (indexFirst != -1 && indexSecond != -1 && indexFirst != indexSecond)
        {
            circuits[indexFirst].insert(circuits[indexSecond].begin(), circuits[indexSecond].end());
            circuits.erase(circuits.begin() + indexSecond);
        }


        if (circuits.size() == 1 && coordinatesInCircuit.size() == coordinates.size())
        {
            return std::get<0>(a.second.first) * std::get<0>(a.second.second);
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day08_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput, 10) == 40);

    FileHandler fileHandler("input-files/2025/day08.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 25272);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 2: " << std::flush << std::setprecision(20) << part2(input) << std::setprecision(-1) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}