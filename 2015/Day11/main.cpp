#include <iostream>
#include <cassert>

#include "StringParser.hpp"
#include "FileHandler.hpp"

// Passwords must include one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz. They cannot skip letters; abd doesn't count.
// Passwords may not contain the letters i, o, or l, as these letters can be mistaken for other characters and are therefore confusing.
// Passwords must contain at least two different, non-overlapping pairs of letters, like aa, bb, or zz.
bool validatePassword(const std::vector<int> & password)
{
    // find increasing straight
    bool increasingStraight = false;
    int increasingNumbers = 1;
    int lastNum = password[0];
    for (int i = 1; i < password.size(); i++)
    {
        if (increasingNumbers == 3)
        {
            increasingStraight = true;
            break;
        }
        if (password[i] == lastNum+1)
        {
            increasingNumbers++;
        }
        else
        {
            increasingNumbers = 1;
        }
        lastNum = password[i];
    }

    // i o and l are not allowed
    bool allLettersAllowed = true;
    for (const int & elem : password)
    {
        if ((elem == 'i' - 96) || (elem == 'o' - 96) || (elem == 'l' - 96)) 
        {
            allLettersAllowed = false;
            break;
        }
    }

    // find pairs
    bool firstpair = false;
    bool secondpair = false;
    for (int i = 0; i < password.size(); i++)
    {
        if (password[i] == password[i+1])
        {
            if (firstpair)
            {
                secondpair = true;
            }
            else
            {
                firstpair = true;
            }
            i += 1;
        }
    }

    return increasingStraight && allLettersAllowed && firstpair && secondpair;
}

void getNextPassword(std::vector<int> & password)
{
    do
    {
        password[password.size()-1]++;
        for (int i = password.size() - 1; i > 0; i--)
        {
            if (password[i] > 26)
            {
                password[i] = 1;
                password[i-1] += 1;
            }
            else
            {
                break;
            }
        }
    } while (!validatePassword(password));
    
}

std::string part1(std::vector<std::string> input)
{
    std::string result;
    std::vector<int> password; // represent password as vector of ints to be able to generate new ones faster
    for (const char & c : input[0])
    {
        password.push_back(c - 96);
    }
    
    getNextPassword(password);
    for (const int & elem : password)
    {
        result += (elem + 96);
    }
    return result;
}

std::string part2(std::vector<std::string> input)
{
    std::string result;
    std::vector<int> password; // represent password as vector of ints to be able to generate new ones faster
    for (const char & c : input[0])
    {
        password.push_back(c - 96);
    }
    
    getNextPassword(password); // first time expired
    getNextPassword(password); // expired again
    for (const int & elem : password)
    {
        result += (elem + 96);
    }
    return result;
}

int main(void) 
{
    FileHandler fileHandler("input-files/2015/day11.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}