#include <iostream>
#include <map>
#include <set>
#include <chrono>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::set< std::vector<std::string> > findAllPaths(std::vector< std::vector<std::string> > roughMap, bool visitSmallCaveTwice = false)
{
    std::map< std::string, std::vector<std::string> > options;
    for (std::vector<std::string> entry : roughMap)
    {
        if (entry[0] != "start" && entry[1] != "end")
        {
            options[entry[1]].push_back(entry[0]);
        }
        options[entry[0]].push_back(entry[1]);
    }

    std::vector<std::string> smallCaves;
    for (auto destination : options)
    {
        if (std::all_of(destination.first.begin(), destination.first.end(), [](unsigned char c){ return std::islower(c); }) && destination.first != "start" && destination.first != "end")
        {
            smallCaves.push_back(destination.first);
        }
    }
    
    std::set< std::vector<std::string> > paths;
    std::set< std::vector<std::string> > unfinishedPaths;
    std::vector<std::string> startPath = {"start"};
    unfinishedPaths.insert(startPath);
    while (unfinishedPaths.size() > 0)
    {
        std::set< std::vector<std::string> > oldPaths = paths;
        std::vector< std::vector<std::string> > deadEnds;
        std::vector< std::vector<std::string> > unfinishedPathsToAdd;
        std::set< std::vector<std::string> > unfinishedPathsCopy = unfinishedPaths;
        for (const std::vector<std::string> & path : unfinishedPathsCopy)
        {
            std::string currentPosition = path.back();
            if (options[currentPosition].size() > 1)
            {
                std::vector< std::vector<std::string> > copies(options[currentPosition].size() - 1, path);
                // must create copies
                for (int i = 1; i < options[currentPosition].size(); i++)
                {
                    if (std::all_of(options[currentPosition][i].begin(), options[currentPosition][i].end(), [](unsigned char c){ return std::isupper(c); }) ||
                        std::find(copies[i-1].begin(), copies[i-1].end(), options[currentPosition][i]) == copies[i-1].end() ||
                        (visitSmallCaveTwice && std::count(path.begin(), path.end(), options[currentPosition][i]) == 1 && std::count_if(smallCaves.begin(), smallCaves.end(), [&](std::string destination){ return std::count(path.begin(), path.end(), destination) == 2; }) == 0 && std::find(smallCaves.begin(), smallCaves.end(), options[currentPosition][i]) != smallCaves.end()))
                    {
                        copies[i - 1].push_back(options[currentPosition][i]);
                        unfinishedPathsToAdd.push_back(copies[i-1]);
                    }
                }
            }

            if (std::all_of(options[currentPosition][0].begin(), options[currentPosition][0].end(), [](unsigned char c){ return std::isupper(c); }) ||
                std::find(path.begin(), path.end(), options[currentPosition][0]) == path.end() ||
                (visitSmallCaveTwice && std::count(path.begin(), path.end(), options[currentPosition][0]) == 1 && std::count_if(smallCaves.begin(), smallCaves.end(), [&](std::string destination){ return std::count(path.begin(), path.end(), destination) == 2; }) == 0 && std::find(smallCaves.begin(), smallCaves.end(), options[currentPosition][0]) != smallCaves.end()))
            {
                std::vector<std::string> tmp = path;
                unfinishedPaths.erase(path);
                tmp.push_back(options[currentPosition][0]);
                unfinishedPaths.insert(tmp);
            }
            else 
            {
                std::vector<std::string> tmp = path;
                unfinishedPaths.erase(path);
                tmp.push_back(options[currentPosition][0]);
                unfinishedPaths.insert(tmp);
                deadEnds.push_back(tmp);
            }
        }
        
        unfinishedPaths.insert(unfinishedPathsToAdd.begin(), unfinishedPathsToAdd.end());
        
        // remove dead ends
        for (const std::vector<std::string> & deadEnd : deadEnds)
        {
            unfinishedPaths.erase(deadEnd);
        }

        unfinishedPathsCopy = unfinishedPaths;
        for (const std::vector<std::string> & path: unfinishedPathsCopy)
        {
            if (path.back() == "end")
            {
                //finished path
                paths.insert(path);
                unfinishedPaths.erase(path);
            }
        }
    }

    return paths;
}

std::vector< std::vector<std::string> > splitVectors(const std::vector<std::string> & src, const std::string & delimiter)
{
    std::vector< std::vector<std::string> > result;
    for (std::string item : src)
    {
        result.push_back(StringParser::toVector(item, delimiter));
    }
    return result;
}

int main(void)
{
    std::vector< std::vector<std::string> > testInput1 = splitVectors(StringParser::toVector("start-A\nstart-b\nA-c\nA-b\nb-d\nA-end\nb-end", "\n"), "-");
    assert(findAllPaths(testInput1).size() == 10);
    
    std::vector< std::vector<std::string> > testInput2 = splitVectors(StringParser::toVector("dc-end\nHN-start\nstart-kj\ndc-start\ndc-HN\nLN-dc\nHN-end\nkj-sa\nkj-HN\nkj-dc", "\n"), "-");
    assert(findAllPaths(testInput2).size() == 19);
    
    std::vector< std::vector<std::string> > testInput3 = splitVectors(StringParser::toVector("fs-end\nhe-DX\nfs-he\nstart-DX\npj-DX\nend-zg\nzg-sl\nzg-pj\npj-he\nRW-he\nfs-DX\npj-RW\nzg-RW\nstart-pj\nhe-WI\nzg-he\npj-fs\nstart-RW", "\n"), "-");
    assert(findAllPaths(testInput3).size() == 226);
    
    FileHandler fileHandler("input-files/2021/day12.txt");
    std::vector< std::vector<std::string> > input = splitVectors(StringParser::toVector(fileHandler.getBuffer(), "\n"), "-");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 1: " << std::flush << findAllPaths(input).size() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(findAllPaths(testInput1, true).size() == 36);
    assert(findAllPaths(testInput2, true).size() == 103);
    assert(findAllPaths(testInput3, true).size() == 3509);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 2: " << std::flush << findAllPaths(input, true).size() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
