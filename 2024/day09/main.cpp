#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

unsigned long long part1(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;
    
    std::string diskmap = input[0];
    
    std::vector<int> filemap;

    int totalAmountOfFilledSlots = 0;
    for (int i = 0; i < diskmap.size(); i++)
    {
        if (i % 2 == 0)
        {
            totalAmountOfFilledSlots += (diskmap[i] - '0');
        }
    }

    int lowID = 0;
    int lowIterator = 0;
    int lowAmountLeft = diskmap[lowIterator] - '0';

    int highID = diskmap.size() / 2;
    int highIterator = diskmap.size() - 1;
    int highAmountLeft = diskmap[highIterator] - '0';

    for (int slot = 1; slot <= totalAmountOfFilledSlots; slot++)
    {
        while (lowAmountLeft == 0)
        {
            if (lowIterator % 2 == 0)
            {
                lowID++;
            }
            lowIterator++;
            lowAmountLeft = diskmap[lowIterator] - '0';
        }
        while (highAmountLeft == 0)
        {
            highIterator -= 2;
            highID--;
            highAmountLeft = diskmap[highIterator] - '0';
        }

        if (lowIterator % 2 == 0)
        {
            filemap.push_back(lowID);
            lowAmountLeft--;
        }
        else
        {
            filemap.push_back(highID);
            highAmountLeft--;
            lowAmountLeft--;
        }
    }

    for (int i = 0; i < filemap.size(); i++)
    {
        result += i * filemap[i];
    }

    return result;
}

unsigned long long part2(const std::vector<std::string> & input) 
{
    unsigned long long result = 0;
    
    std::string diskmap = input[0];
    
    std::vector<int> filemap;
    std::set<int> movedFilesIndices;
    int id = 0;

    for (int i = 0; i < diskmap.size(); i++)
    {
        // if the index is even then we cannot move it
        if (i % 2 == 0)
        {   
            // check if the file at this index already was moved
            bool fileMoved = (movedFilesIndices.find(i) != movedFilesIndices.end());
            for (int n = 0; n < diskmap[i] - '0'; n++)
            {
                if (fileMoved)
                {
                    filemap.push_back(0);
                }
                else 
                {
                    filemap.push_back(id);
                }
            }
            id++;
        }
        else
        {
            int freeSpace = diskmap[i] - '0';
            int j = diskmap.size() - 1;
            int highID = diskmap.size() / 2;

            // move j to index of first possible file that may be moved
            while (movedFilesIndices.find(j) != movedFilesIndices.end())
            {
                j -= 2;
                highID--;
            }

            // as long as there is free space keep filling it
            while (freeSpace > 0)
            {
                if (j > i)
                {
                    if ((diskmap[j] - '0') <= freeSpace)
                    {
                        for (int n = 0; n < (diskmap[j] - '0'); n++)
                        {
                            filemap.push_back(highID);
                            freeSpace--;
                        }
                        movedFilesIndices.insert(j);
                    }

                    do
                    {
                        j -= 2;
                        highID--;

                    } while (movedFilesIndices.find(j) != movedFilesIndices.end());
                }
                else
                {
                    filemap.push_back(0);
                    freeSpace--;
                }
            }
        }
    }

    for (int i = 0; i < filemap.size(); i++)
    {
        result += i * filemap[i];
    }

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day09_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");
    assert(part1(testinput) == 60);
    
    FileHandler testFileHandler2("input-files/2024/day09_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n");
    assert(part1(testinput2) == 1928);

    FileHandler fileHandler("input-files/2024/day09.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput2) == 2858);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}