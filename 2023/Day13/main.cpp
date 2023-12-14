#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <utility>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::vector<int> getReflectionLines(const std::vector<std::string> & src)
{
    std::vector<int> result;
    for (int i = 1; i < src.size(); i++)
    {
        if (src[i] == src[i-1])
        {
            for (int j = 0; j + i <= src.size(); j++)
            {
                if (i-(1+(1*j)) < 0 || j+i == src.size())
                {
                    result.push_back(i);
                    break;
                }
                else if (src[i+j] != src[i-(1+(1*j))])
                {
                    break;
                }
            }
        }
    }
    return result;
}

std::vector<int> summarize(std::vector<std::string> parsed)
{
    std::vector<int> result;
    
    std::vector<int> reflectionLines = getReflectionLines(parsed);
    for (int i = 0; i < reflectionLines.size(); i++)
    {
        result.push_back(100 * reflectionLines[i]);
    }

    std::vector<std::string> turnedRight;
    for (int y = 0; y < parsed[0].size(); y++)
    {
        std::string str;
        for (int x = 0; x < parsed.size(); x++)
        {
            str = parsed[x][y] + str;
        }
        turnedRight.push_back(str);
    }

    reflectionLines = getReflectionLines(turnedRight);
    for (int i = 0; i < reflectionLines.size(); i++)
    {
        result.push_back(reflectionLines[i]);
    }


    return result;
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    for (const std::string & line : input)
    {
        std::vector<std::string> parsed = StringParser::toVector(line, "\n");
        result += summarize(parsed)[0];
    }

    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    int num = 1;
    for (std::string line : input)
    {
        num++;

        std::string original = line;
        std::vector<std::string> originalParsed = StringParser::toVector(original, "\n");
        int originalSummarized = summarize(originalParsed)[0];

        // remove smudge
        for (int i = 0; i < line.size(); i++)
        {
            if (i > 0)
            {
                if (line[i - 1] == '#')
                {
                    line[i - 1] = '.';
                }
                else 
                {
                    line[i - 1] = '#';
                }
            }
            bool newLineFound = (line[i] == '\n');
            if (newLineFound) { i++; }
            if (line[i] == '#')
            {
                line[i] = '.';
            }
            else 
            {
                line[i] = '#';
            }

            std::vector<std::string> parsed = StringParser::toVector(line, "\n");
            
            std::vector<int> summarized = summarize(parsed);
            bool foundNewVal = false;
            for (int i = 0; i < summarized.size(); i++)
            {
                if (summarized[i] > 0 && summarized[i] != originalSummarized)
                {
                    foundNewVal = true;
                    result += summarized[i];
                    break;
                }
            }
            if (foundNewVal) { break; }
        }
    }
    
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day13_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n\n");
    assert(part1(testInput) == 405);

    FileHandler fileHandler("input-files/2023/day13.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    assert(part2(testInput) == 400);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 13, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}