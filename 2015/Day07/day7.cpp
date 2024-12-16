#include <iostream>
#include <map>
#include <cctype>
#include <algorithm>

#include "StringParser.hpp"
#include "FileHandler.hpp"

void executeAndSortInstructions(std::vector<std::string>& instructions, std::map<std::string, unsigned short>& wires)
{
    std::vector<std::string> known_outputs;

    std::vector<std::string> sorted_instructions;
    while (instructions.size() > 0)
    {
        int i = 0;
        for (; i < instructions.size(); i++)
        {
            std::vector<std::string> instruction_elements = StringParser::toVector(instructions[i], " ");
            if (instructions[i].find("AND") != std::string::npos)
            {
                if ((instruction_elements[0].find_first_not_of("0123456789") == std::string::npos ? true : std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[0]) != known_outputs.end()) && std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[2]) != known_outputs.end())
                {
                    wires[instruction_elements[4]] = (instruction_elements[0].find_first_not_of("0123456789") == std::string::npos ? (unsigned short)std::stoi(instruction_elements[0]) : wires[instruction_elements[0]]) & wires[instruction_elements[2]];
                    known_outputs.push_back(instruction_elements[4]);
                    break;
                }
            }
            else if (instructions[i].find("LSHIFT") != std::string::npos)
            {
                if (std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[0]) != known_outputs.end())
                {
                    wires[instruction_elements[4]] = wires[instruction_elements[0]] << std::stoi(instruction_elements[2]);
                    known_outputs.push_back(instruction_elements[4]);
                    break;
                }
            }
            else if (instructions[i].find("RSHIFT") != std::string::npos)
            {
                if (std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[0]) != known_outputs.end())
                {
                    wires[instruction_elements[4]] = wires[instruction_elements[0]] >> std::stoi(instruction_elements[2]);
                    known_outputs.push_back(instruction_elements[4]);
                    break;
                }
            }
            else if (instructions[i].find("NOT") != std::string::npos)
            {
                if (std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[1]) != known_outputs.end())
                {
                    wires[instruction_elements[3]] = ~wires[instruction_elements[1]];
                    known_outputs.push_back(instruction_elements[3]);
                    break;
                }
            }
            else if (instructions[i].find("OR") != std::string::npos)
            {
                if ((instruction_elements[0].find_first_not_of("0123456789") == std::string::npos ? true : std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[0]) != known_outputs.end()) && std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[2]) != known_outputs.end())
                {
                    wires[instruction_elements[4]] = wires[instruction_elements[0]] | wires[instruction_elements[2]];
                    known_outputs.push_back(instruction_elements[4]);
                    break;
                }
            }
            else 
            {
                if (instruction_elements[0].find_first_not_of("0123456789") == std::string::npos ? true : std::find(known_outputs.begin(), known_outputs.end(), instruction_elements[0]) != known_outputs.end())
                {
                    wires[instruction_elements[2]] = instruction_elements[0].find_first_not_of("0123456789") == std::string::npos ? std::stoi(instruction_elements[0]) : wires[instruction_elements[0]];
                    known_outputs.push_back(instruction_elements[2]);
                    break;
                }
            }
        }
        if (i != instructions.size())
        {
            sorted_instructions.push_back(instructions[i]);
            instructions.erase(instructions.begin() + i);
        }
    }
    instructions = sorted_instructions;
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day07.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();

    std::cout << "Day 7, puzzle 1: ";
    std::map<std::string, unsigned short> wires;
    executeAndSortInstructions(input, wires);
    std::cout << wires["a"] << std::endl;

    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    
    std::cout << "Day 7, puzzle 2: ";

    // set input of a to b by changing instructions to set that value to b
    int i = 0;
    for (; i < input.size(); i++)
    {
        if (*(StringParser::toVector(input[i], " ").rbegin()) == "b")
        {
            break;
        }
    }
    input[i] = std::to_string(wires["a"]) + " -> b";
    executeAndSortInstructions(input, wires);
    std::cout << wires["a"] << std::endl;

    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}