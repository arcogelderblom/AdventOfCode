#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <algorithm>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::vector<std::vector<long long>> parseToMap(const std::string & str)
{
    std::vector<std::vector<long long>> result;
    std::vector<std::string> parsed = StringParser::toVector(str, "\n");
    for (int i = 1; i < parsed.size(); i++)
    {
        result.push_back(StringParser::toLongLongVector(parsed[i], " "));
    }
    return result;
}

long long findMappedValue(const long long & currentX, const std::vector<std::vector<long long>> & xToYMap)
{
    for (const std::vector<long long> & xToY : xToYMap)
    {
        if ((currentX >= xToY[1]) && currentX < (xToY[1] + xToY[2]))
        {
            return xToY[0] + (currentX - xToY[1]);
        }
    }
    return currentX;
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = std::numeric_limits<long long>::max();
    std::vector<long long> seeds = StringParser::toLongLongVector(input[0].substr(std::string("seeds: ").size()), " ");
    std::vector<std::vector<long long>> seedToSoilMap = parseToMap(input[1]);
    std::vector<std::vector<long long>> soilToFertilizerMap = parseToMap(input[2]);
    std::vector<std::vector<long long>> fertilizerToWaterMap = parseToMap(input[3]);
    std::vector<std::vector<long long>> waterToLightMap = parseToMap(input[4]);
    std::vector<std::vector<long long>> lightToTemperatureMap = parseToMap(input[5]);
    std::vector<std::vector<long long>> temperatureToHumidityMap = parseToMap(input[6]);
    std::vector<std::vector<long long>> humidityToLocationMap = parseToMap(input[7]);
    
    for (const long long & seed : seeds)
    {
        long long soil = findMappedValue(seed, seedToSoilMap);
        long long fertilizer = findMappedValue(soil, soilToFertilizerMap);
        long long water = findMappedValue(fertilizer, fertilizerToWaterMap);
        long long light = findMappedValue(water, waterToLightMap);
        long long temperature = findMappedValue(light, lightToTemperatureMap);
        long long humidity = findMappedValue(temperature, temperatureToHumidityMap);
        long long location = findMappedValue(humidity, humidityToLocationMap);
        
        if (location < result)
        {
            result = location;
        }
    }


    return result;
}

long long part2(const std::vector<std::string> & input, int step = 1) 
{
    long long result = std::numeric_limits<long long>::max();
    std::vector<long long> seeds = StringParser::toLongLongVector(input[0].substr(std::string("seeds: ").size()), " ");
    std::vector<std::vector<long long>> seedToSoilMap = parseToMap(input[1]);
    std::vector<std::vector<long long>> soilToFertilizerMap = parseToMap(input[2]);
    std::vector<std::vector<long long>> fertilizerToWaterMap = parseToMap(input[3]);
    std::vector<std::vector<long long>> waterToLightMap = parseToMap(input[4]);
    std::vector<std::vector<long long>> lightToTemperatureMap = parseToMap(input[5]);
    std::vector<std::vector<long long>> temperatureToHumidityMap = parseToMap(input[6]);
    std::vector<std::vector<long long>> humidityToLocationMap = parseToMap(input[7]);
    
    long long seedWithLowestLocation = 0;
    for (int i = 0; i < seeds.size(); i+=2)
    {
        for (long long j = seeds[i]; j < seeds[i] + seeds[i + 1]; j+=step)
        {
            long long soil = findMappedValue(j, seedToSoilMap);
            long long fertilizer = findMappedValue(soil, soilToFertilizerMap);
            long long water = findMappedValue(fertilizer, fertilizerToWaterMap);
            long long light = findMappedValue(water, waterToLightMap);
            long long temperature = findMappedValue(light, lightToTemperatureMap);
            long long humidity = findMappedValue(temperature, temperatureToHumidityMap);
            long long location = findMappedValue(humidity, humidityToLocationMap);
            if (location < result)
            {
                result = location;
                seedWithLowestLocation = j;
            }
        }
    }

    for (long long j = seedWithLowestLocation-step; j < seedWithLowestLocation + step*2; j++)
    {
        long long soil = findMappedValue(j, seedToSoilMap);
        long long fertilizer = findMappedValue(soil, soilToFertilizerMap);
        long long water = findMappedValue(fertilizer, fertilizerToWaterMap);
        long long light = findMappedValue(water, waterToLightMap);
        long long temperature = findMappedValue(light, lightToTemperatureMap);
        long long humidity = findMappedValue(temperature, temperatureToHumidityMap);
        long long location = findMappedValue(humidity, humidityToLocationMap);
        if (location < result)
        {
            result = location;
            seedWithLowestLocation = j;
        }
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day05_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n\n");
    assert(part1(testInput) == 35);

    FileHandler fileHandler("input-files/2023/day05.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 46);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 2: " << std::flush << part2(input, 10000) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}