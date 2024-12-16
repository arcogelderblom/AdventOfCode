#include <iostream>

#include "StringParser.hpp"
#include "FileHandler.hpp"

int part1(std::vector<std::string> all_lines)
{
    int code_character_num = 0;
    int memory_character_num = 0;
    for (const std::string& line : all_lines)
    {
        code_character_num += line.size();
        std::string l = line.substr(1, line.size() - 2);
        for (int i = 0; i < l.size(); i++)
        {
            if (l[i] == '\\')
            {
                if (l[i+1] != 'x')
                {
                    memory_character_num++;
                    i++;
                }
                else 
                {
                    memory_character_num++;
                    i+=3;
                }
            }
            else 
            {
                memory_character_num++;
            }
        }
    }
    return std::abs(code_character_num - memory_character_num);
}

int part2(std::vector<std::string> all_lines)
{
    int code_character_num = 0;
    int new_encoded_string_character_num = 0;
    for (const std::string& line : all_lines)
    {
        code_character_num += line.size();
        for (char c : line)
        {
            if (!isalnum(c))
            {
                new_encoded_string_character_num += 2;
            }
            else 
            {
                new_encoded_string_character_num++;
            }
        }
        new_encoded_string_character_num += 2;
    }
    return std::abs(new_encoded_string_character_num - code_character_num);
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day08.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 2: " << std::flush << part2(input)  << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}