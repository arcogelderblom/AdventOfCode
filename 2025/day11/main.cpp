#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include <map>
#include <set>

int getAllRoutesPart1(std::map<std::string, std::vector<std::string>> devicesAndOutputs, std::string current, const std::string & final)
{
    if (current == final)
    {
        return 1;
    }
    int result = 0;
    for (const std::string & output : devicesAndOutputs[current])
    {
        result += getAllRoutesPart1(devicesAndOutputs, output, final);
    }
    // std::cout << result << std::endl;
    return result;
}

long long getAllRoutesPart2(std::map<std::string, std::vector<std::string>> devicesAndOutputs, std::string current, const std::string & final, std::map<std::tuple<std::string, bool, bool>, long long> & cache, bool seenFFT = false, bool seenDAC = false)
{
    if (cache.find({current, seenFFT, seenDAC}) != cache.end())
    {
        return cache[{current, seenFFT, seenDAC}];
    }
    
    if (current == final && seenFFT && seenDAC)
    {
        return 1;
    }

    if (current == "fft")
    {
        seenFFT = true;
    }
    else if (current == "dac")
    {
        seenDAC = true;
    }

    long long result = 0;
    for (const std::string & output : devicesAndOutputs[current])
    {
        long long resultOutput = getAllRoutesPart2(devicesAndOutputs, output, final, cache, seenFFT, seenDAC);
        result += resultOutput;
        cache[{output, seenFFT, seenDAC}] = resultOutput;
    }

    return result;
}

int part1(const std::vector<std::string> & input)
{
    std::map<std::string, std::vector<std::string>> devicesAndOutputs;
    for (const std::string & line : input)
    {
        devicesAndOutputs[line.substr(0, 3)] = StringParser::toVector(line.substr(5), " ");
    }
    return getAllRoutesPart1(devicesAndOutputs, "you", "out");
}

long long part2(const std::vector<std::string> & input) 
{
    std::map<std::string, std::vector<std::string>> devicesAndOutputs;
    for (const std::string & line : input)
    {
        devicesAndOutputs[line.substr(0, 3)] = StringParser::toVector(line.substr(5), " ");
    }

    std::map<std::string, std::vector<std::string>> nextFromCurrent;
    std::map<std::tuple<std::string, bool, bool>, long long> cache;
    return getAllRoutesPart2(devicesAndOutputs, "svr", "out", cache);
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2025/day11_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 5);

    FileHandler fileHandler("input-files/2025/day11.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    FileHandler testFile2Handler("input-files/2025/day11_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFile2Handler.getBuffer(), "\n");
    assert(part2(testinput2) == 2);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}