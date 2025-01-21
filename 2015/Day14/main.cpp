#include <iostream>
#include <cassert>

#include <map>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int part1(std::vector<std::string> input)
{
    int result = 0;
    
    for (const std::string & line : input)
    {
        std::string reindeer = line.substr(0, line.find(' '));
        int kms = std::stoi(line.substr(line.find("fly") + 4, line.find(' ', line.find("fly") + 4)));
        int flighttime = std::stoi(line.substr(line.find("for") + 4, line.find(' ', line.find("for") + 4)));
        int resttime = std::stoi(line.substr(line.find("for", line.find("rest")) + 4, line.find(' ', line.find("for", line.find("rest")) + 4)));
        
        int traveltime = 2503;
        bool flying = true;
        int distancetravelled = 0;
        while (traveltime > 0)
        {
            if (flying)
            {
                if (flighttime <= traveltime)
                {
                    distancetravelled += kms * flighttime;
                    traveltime -= flighttime;
                    flying = false;
                }
                else
                {
                    distancetravelled += kms * traveltime;
                    traveltime = 0;
                    flying = false;
                }
            }
            else
            {
                traveltime -= resttime;
                flying = true;
            }
        }
        if (distancetravelled > result)
        {
            result = distancetravelled;
        }
    }

    return result;
}

struct Reindeer
{
    std::string name;
    int kms;
    int flighttime;
    int flighttimeremaining;
    int resttime;
    int resttimeremaining;
    bool flying = true;
    int distancetravelled = 0;
};

int part2(std::vector<std::string> input)
{
    int result = 0;

    std::vector<Reindeer> allReindeer;
    for (const std::string & line : input)
    {
        // Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
        std::string name = line.substr(0, line.find(' '));
        int kms = std::stoi(line.substr(line.find("fly") + 4, line.find(' ', line.find("fly") + 4)));
        int flighttime = std::stoi(line.substr(line.find("for") + 4, line.find(' ', line.find("for") + 4)));
        int resttime = std::stoi(line.substr(line.find("for", line.find("rest")) + 4, line.find(' ', line.find("for", line.find("rest")) + 4)));

        Reindeer current;
        current.name = name;
        current.kms = kms;
        current.flighttime = flighttime;
        current.flighttimeremaining = flighttime;
        current.resttime = resttime;
        current.resttimeremaining = resttime;
        allReindeer.push_back(current);
    }

    std::map<std::string, int> scores;
    for (int second = 0; second < 2503; second++)
    {
        std::map<int, std::vector<std::string>> distances;
        for (Reindeer & reindeer : allReindeer)
        {
            if (reindeer.flying)
            {
                reindeer.distancetravelled += reindeer.kms;
                reindeer.flighttimeremaining -= 1;
                if (reindeer.flighttimeremaining == 0)
                {
                    reindeer.flying = false;
                    reindeer.flighttimeremaining = reindeer.flighttime;
                }
            }
            else
            {
                reindeer.resttimeremaining -= 1;
                if (reindeer.resttimeremaining == 0)
                {
                    reindeer.flying = true;
                    reindeer.resttimeremaining = reindeer.resttime;
                }
            }
            distances[reindeer.distancetravelled].push_back(reindeer.name);
        }

        for (const std::string & name : distances.rbegin()->second)
        {
            scores[name]++;
        }
    }

    for (const std::pair<std::string, int> score : scores)
    {
        if (score.second > result)
        {
            result = score.second;
        }
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2015/day14_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput) == 2660);

    FileHandler fileHandler("input-files/2015/day14.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 1564);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}