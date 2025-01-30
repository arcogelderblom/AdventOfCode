#include <iostream>
#include <cassert>

#include <map>

#include "StringParser.hpp"
#include "FileHandler.hpp"

void getOptions(int ingredients, std::vector<std::vector<int>> & options, int maxAmount = 100, int amountUsed = 0, std::vector<int> current = std::vector<int>())
{
    if (ingredients == 0)
    {
        options.push_back(current);
        return;
    }
    if (ingredients > 1)
    {
        for (int currentAmount = 0; currentAmount <= maxAmount - amountUsed; currentAmount++)
        {
            current.push_back(currentAmount);
            getOptions(ingredients - 1, options, maxAmount, amountUsed + currentAmount, current);
            current.pop_back();
        }
    }
    else
    {
        current.push_back(maxAmount - amountUsed);
        getOptions(ingredients - 1, options, maxAmount, amountUsed + (maxAmount - amountUsed), current);
        current.pop_back();
    }
}

unsigned long long part1(std::vector<std::string> input)
{
    unsigned long long result = 0;
    
    std::map<std::string, std::vector<int>> ingredients;
    std::vector<std::string> ingredientNames;
    for (const std::string & line : input)
    {
        std::string name = line.substr(0, line.find(':'));
        std::vector<std::string> elements = StringParser::toVector(line.substr(line.find(": ") + 2), ", ");
        ingredients[name].push_back(std::stoi(elements[0].substr(elements[0].find(' '))));
        ingredients[name].push_back(std::stoi(elements[1].substr(elements[1].find(' '))));
        ingredients[name].push_back(std::stoi(elements[2].substr(elements[2].find(' '))));
        ingredients[name].push_back(std::stoi(elements[3].substr(elements[3].find(' '))));
        // ingredients[name].push_back(std::stoi(elements[4].substr(elements[4].find(' ')))); // ignore calories in part 1
        ingredientNames.push_back(name);
    }

    std::vector<std::vector<int>> options;
    getOptions(ingredients.size(), options);
    
    for (const std::vector<int> & option : options)
    {
        std::map<std::string, int> ingredientAndAmount;
        for (int i = 0; i < option.size(); i++)
        {
            ingredientAndAmount[ingredientNames[i]] = option[i];
        }

        std::vector<int> values;
        for (int i = 0; i < ingredients.begin()->second.size(); i++)
        {
            int currentValue = 0;
            for (const std::string & name : ingredientNames)
            {
                currentValue += ingredients[name][i] * ingredientAndAmount[name];
            }
            if (currentValue < 0) { currentValue = 0; }
            values.push_back(currentValue);
        }

        unsigned long long score = 1;
        for (const int & value : values)
        {
            score *= value;
        }

        if (score > result)
        {
            result = score;
        }
    }
    return result;
}

unsigned long long part2(std::vector<std::string> input)
{ 
    unsigned long long result = 0;
    
    std::map<std::string, std::vector<int>> ingredients;
    std::vector<std::string> ingredientNames;
    for (const std::string & line : input)
    {
        std::string name = line.substr(0, line.find(':'));
        std::vector<std::string> elements = StringParser::toVector(line.substr(line.find(": ") + 2), ", ");
        ingredients[name].push_back(std::stoi(elements[0].substr(elements[0].find(' '))));
        ingredients[name].push_back(std::stoi(elements[1].substr(elements[1].find(' '))));
        ingredients[name].push_back(std::stoi(elements[2].substr(elements[2].find(' '))));
        ingredients[name].push_back(std::stoi(elements[3].substr(elements[3].find(' '))));
        ingredients[name].push_back(std::stoi(elements[4].substr(elements[4].find(' ')))); 
        ingredientNames.push_back(name);
    }

    std::vector<std::vector<int>> options;
    getOptions(ingredients.size(), options);
    
    for (const std::vector<int> & option : options)
    {
        std::map<std::string, int> ingredientAndAmount;
        for (int i = 0; i < option.size(); i++)
        {
            ingredientAndAmount[ingredientNames[i]] = option[i];
        }

        std::vector<int> values;
        for (int i = 0; i < ingredients.begin()->second.size(); i++)
        {
            int currentValue = 0;
            for (const std::string & name : ingredientNames)
            {
                currentValue += ingredients[name][i] * ingredientAndAmount[name];
            }
            if (currentValue < 0) { currentValue = 0; } 
            values.push_back(currentValue);
        }

        unsigned long long score = 1;
        for (int i = 0; i < values.size() - 1; i++) // smaller than size - 1 because ignore calories in calculation
        {
            score *= values[i];
        }

        if (score > result && *(values.rbegin()) == 500) // check to find largest score when the last one (calories) is equal to 500
        {
            result = score;
        }
    }
    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2015/day15_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n");

    assert(part1(testinput) == 62842880);

    FileHandler fileHandler("input-files/2015/day15.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testinput) == 57600000);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}