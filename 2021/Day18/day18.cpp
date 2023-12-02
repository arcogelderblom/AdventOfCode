#include <iostream>
#include <chrono>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

bool explode(std::string& current)
{
    bool exploded = false;
    int nested = 0;
    for (int i = 0; i < current.size(); i++)
    {
        if (current[i] == '[')
        {
            nested++;
            if (nested == 5)
            {
                // current is nested, explode.
                exploded = true;
                std::vector<std::string> currentSeparated = StringParser::toVector(current.substr(i+1, current.find_first_of("]", i) - i - 1), ",");
                std::string leftSide = current.substr(0, i + 1);
                std::reverse(leftSide.begin(), leftSide.end());
                if (leftSide.find_last_not_of("[,]") != std::string::npos)
                {
                    int index = leftSide.find_first_not_of("[,]");
                    std::string num = leftSide.substr(index, leftSide.find_first_of("[,", index) - index);
                    std::reverse(num.begin(), num.end());
                    current.replace(i - index - (num.size() - 1), num.size(), std::to_string(std::stoi(num) + std::stoi(currentSeparated[0])));
                    i += (std::to_string(std::stoi(num) + std::stoi(currentSeparated[0])).size() - num.size());
                }
              
                if (current.find_first_not_of("[,]", current.find_first_of("]", i)) != std::string::npos)
                {
                    int index = current.find_first_not_of("[,]", current.find_first_of("]", i));
                    std::string num = current.substr(index, current.find_first_of("],", index) - index);
                    current.replace(index, num.size(), std::to_string(std::stoi(num) + std::stoi(currentSeparated[1])));
                }

                current.replace(i, current.find_first_of("]", i) - i + 1, "0");

                break;
            }
        }
        else if (current[i] == ']')
        {
            nested--;
        }
    }
    return exploded;
}

bool split(std::string& current)
{
    bool splitted = false;
    int nested = 0;
    for (int i = 0; i < current.size(); i++)
    {
        int indexStart = current.find_first_not_of("[,]", i);
        int indexEnd = current.find_first_of("[,]", i);
        if (indexStart == std::string::npos || indexEnd == std::string::npos)
        {
            break;
        }

        if (indexEnd - indexStart > 1)
        {
            splitted = true;
            int currentNum = std::stoi(current.substr(indexStart, indexEnd));
            int leftSide = currentNum / 2;
            std::string toInsert = "[" + std::to_string(leftSide) + "," + std::to_string(currentNum - leftSide) + "]";
            current.replace(indexStart, indexEnd - indexStart, toInsert);
            break;
        }
        else 
        {
            i = indexEnd;
        }
    }
    return splitted;
}


int calculateResult(std::string current)
{
    int times = 0;
    while (current.find('[') != std::string::npos)
    {

        int iEnd = current.find("]");
        std::string leftSide = current.substr(0, iEnd + 1);
        std::reverse(leftSide.begin(), leftSide.end());
        int iStart = iEnd - leftSide.find("[");
        std::vector<std::string> currentSeparated = StringParser::toVector(current.substr(iStart + 1, iEnd - 1), ",");
        current.replace(iStart, iEnd - iStart + 1, std::to_string(3 * std::stoi(currentSeparated[0]) + 2 * std::stoi(currentSeparated[1])));
    }
    return std::stoi(current);
}

int getMagnitude(std::vector<std::string> homework)
{
    std::string current = homework[0];
    for (int i = 1; i < homework.size(); i++)
    {
        current = "[" + current + "," + homework[i] + "]";
        bool splittedOrExploded = true;
        while (splittedOrExploded)
        {
            if (explode(current))
            {
                splittedOrExploded = true;
            }
            else if (split(current))
            {
                splittedOrExploded = true;
            }
            else 
            {
                splittedOrExploded = false;
            }
        }
    }

    return calculateResult(current);
}

int getLargestPossibleMagnitude(std::vector<std::string> homework)
{
    int maxMagnitude = 0;
    
    for (int i = 0; i < homework.size() - 1; i++)
    {
        for (int j = 1; j < homework.size(); j++)
        {
            std::vector<std::string> possibilities = { std::string("[" + homework[i] + "," + homework[j] + "]"), std::string("[" + homework[j] + "," + homework[i] + "]")};
            for (std::string possibility : possibilities)
            {
                bool splittedOrExploded = true;
                while (splittedOrExploded)
                {
                    if (explode(possibility))
                    {
                        splittedOrExploded = true;
                    }
                    else if (split(possibility))
                    {
                        splittedOrExploded = true;
                    }
                    else 
                    {
                        splittedOrExploded = false;
                    }
                }
                int result = calculateResult(possibility);
                if (result > maxMagnitude)
                {
                    maxMagnitude = result;
                }
            }
        }
    }
    
    return maxMagnitude;
}

int main(void)
{
    std::vector<std::string> testInput = StringParser::toVector("[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]\n[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]\n[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]\n[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]\n[7,[5,[[3,8],[1,4]]]]\n[[2,[2,2]],[8,[8,1]]]\n[2,9]\n[1,[[[9,3],9],[[9,0],[0,7]]]]\n[[[5,[7,4]],7],1]\n[[[[4,2],2],6],[8,7]]", "\n");
    std::vector<std::string> testInput2 = StringParser::toVector("[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]\n[[[5,[2,8]],4],[5,[[9,9],0]]]\n[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]\n[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]\n[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]\n[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]\n[[[[5,4],[7,7]],8],[[8,3],8]]\n[[9,3],[[9,9],[6,[4,9]]]]\n[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]\n[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]", "\n");
    assert(getMagnitude(testInput) == 3488);
    assert(getMagnitude(testInput2) == 4140);
    
    FileHandler fileHandler("input-files/2021/day18.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 1: " << std::flush << getMagnitude(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getLargestPossibleMagnitude(testInput2) == 3993);    
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 18, puzzle 2: " << std::flush << getLargestPossibleMagnitude(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
