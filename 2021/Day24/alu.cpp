#include "alu.hpp"

#include "StringParser.hpp"

ALU::ALU(std::string input):
    _input(input)
{}

void ALU::executeInstruction(std::string instruction, std::map<std::string, int>& variableAndValues)
{
    std::vector<std::string> instructions = StringParser::toVector(instruction, " ");
    if (instructions[0] == "inp")
    {
        variableAndValues[instructions[1]] = _input[_currentInputIndex] - '0';
        _currentInputIndex++;
    }
    else if (instructions[0] == "add")
    {
        if (instructions[2].find_first_of("xwyz") != std::string::npos)
        {
            variableAndValues[instructions[1]] += variableAndValues[instructions[2]];
        }
        else
        {
            variableAndValues[instructions[1]] += std::stoi(instructions[2]);
        }
        
    }
    else if (instructions[0] == "mul")
    {
        if (instructions[2].find_first_of("xwyz") != std::string::npos)
        {
            variableAndValues[instructions[1]] *= variableAndValues[instructions[2]];
        }
        else
        {
            variableAndValues[instructions[1]] *= std::stoi(instructions[2]);
        }
    }
    else if (instructions[0] == "div")
    {
        if (instructions[2].find_first_of("xwyz") != std::string::npos)
        {
            variableAndValues[instructions[1]] /= variableAndValues[instructions[2]];
        }
        else
        {
            variableAndValues[instructions[1]] /= std::stoi(instructions[2]);
        }
    }
    else if (instructions[0] == "mod")
    {
        if (instructions[2].find_first_of("xwyz") != std::string::npos)
        {
            variableAndValues[instructions[1]] %= variableAndValues[instructions[2]];
        }
        else
        {
            variableAndValues[instructions[1]] %= std::stoi(instructions[2]);
        }
    }
    else if (instructions[0] == "eql")
    {
        if (instructions[2].find_first_of("xwyz") != std::string::npos)
        {
            variableAndValues[instructions[1]] = variableAndValues[instructions[1]] == variableAndValues[instructions[2]];
        }
        else 
        {
            variableAndValues[instructions[1]] = variableAndValues[instructions[1]] == std::stoi(instructions[2]);
        }
    }
}
