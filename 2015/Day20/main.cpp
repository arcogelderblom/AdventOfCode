#include <iostream>
#include <cassert>

#include <set>
#include <map>
#include <numeric>

#include "StringParser.hpp"
#include "FileHandler.hpp"

std::set<int> primes;

void getPrimes(int until)
{
    int prime = 2;
    std::set<int> toCheck;
    // std::set<int> primes;
    for (int num = 2; num <= until; num++)
    {
        toCheck.insert(num);
    }
    while (!toCheck.empty())
    {
        int prime = *toCheck.begin();

        toCheck.erase(prime);
        primes.insert(prime);
        int current = prime;
        while (current < until)
        {
            current += prime;
            toCheck.erase(current);
        }
    }

    // return primes;
}

void getAllFactors(std::vector<int> & allFactors, const std::vector<std::vector<int>> & separatedFactors, int calculation = 1, int currentIndex = 0, int currentDepth = 0)
{
    if (currentIndex == separatedFactors.size())
    {
        allFactors.push_back(calculation);
        return;
    }
    while (currentDepth < separatedFactors[currentIndex].size())
    {
        getAllFactors(allFactors, separatedFactors, calculation * separatedFactors[currentIndex][currentDepth], currentIndex+1);
        currentDepth++;
    }
}

unsigned long long getAmountPresents(int houseNumber, const std::set<int> & primes, bool part2 = false)
{
    unsigned long long presents = 0;
    
    std::map<int, int> primeFactors;
    int left = houseNumber;

    while (left > 1)
    {
        for (const int & prime : primes)
        {
            if (left % prime == 0)
            {
                primeFactors[prime]++;
                left /= prime;
                break;
            }
        }
    }

    std::vector<std::vector<int>> separatedFactors;
    for (const std::pair<int, int> primeFactor : primeFactors)
    {
        std::vector<int> all;
        for (int power = 0; power <= primeFactor.second; power++)
        {
            all.push_back(pow(primeFactor.first, power));
        }
        separatedFactors.push_back(all);
    }
    
    // calculate all factors
    std::vector<int> allFactors;
    getAllFactors(allFactors, separatedFactors);

    if (!part2)
    {
        for (const int & factor : allFactors)
        {
            presents += factor * 10;
        }
    }
    else
    {
        for (const int & factor : allFactors)
        {
            if (houseNumber / factor <= 50)
            {
                presents += factor * 11;
            }
        }
    }
    return presents;
}


int part1(const std::vector<std::string> & input)
{
    int result = 0;
    getPrimes(std::stoi(input[0]) / 10);
    
    int houseNumber = 0;
    int presents = 0;
    while (presents < std::stoi(input[0]))
    {
        houseNumber++;
        presents = getAmountPresents(houseNumber, primes);
    }
    result = houseNumber;
    return result;
}

int part2(const std::vector<std::string> & input)
{ 
    int result = 0;
    // std::set<int> primes = getPrimes(std::stoi(input[0]) / 10);
    
    int houseNumber = 0;
    int presents = 0;
    while (presents < std::stoi(input[0]))
    {
        houseNumber++;
        presents = getAmountPresents(houseNumber, primes, true);
    }
    result = houseNumber;
    return result;
}

int main(void) 
{
    FileHandler fileHandler("input-files/2015/day20.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}