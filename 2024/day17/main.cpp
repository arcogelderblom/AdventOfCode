#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>

#include "FileHandler.hpp"
#include "StringParser.hpp"

long long getComboVal(long long & regA, long long & regB, long long & regC, long long & operand)
{
    switch (operand)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return operand;
        case 4:
            return regA;
        case 5:
            return regB;
        case 6:
            return regC;
        case 7:
            throw std::runtime_error("Invalid program");
    }
    return -1;
}

void adv(long long & regA, long long & regB, long long & regC, long long & operand)
{
    regA /= pow(2, getComboVal(regA, regB, regC, operand));
}


void bxl(long long & regA, long long & regB, long long & regC, long long & operand)
{
    regB ^= operand;
}

void bst(long long & regA, long long & regB, long long & regC, long long & operand)
{
    long long comboVal = getComboVal(regA, regB, regC, operand) % 8;
    regB = comboVal & 7;
}

bool jnz(long long & regA, long long & regB, long long & regC, long long & operand, long long & instructionPosition)
{
    if (regA != 0) 
    {
        instructionPosition = operand;
        return true;
    }
    return false;
}

void bxc(long long & regA, long long & regB, long long & regC, long long & operand)
{
    regB ^= regC;
}

std::string out(long long & regA, long long & regB, long long & regC, long long & operand)
{
    return std::to_string(getComboVal(regA, regB, regC, operand) % 8);
}

void bdv(long long & regA, long long & regB, long long & regC, long long & operand)
{
    regB = regA / pow(2, getComboVal(regA, regB, regC, operand));
}

void cdv(long long & regA, long long & regB, long long & regC, long long & operand)
{
    regC = regA / pow(2, getComboVal(regA, regB, regC, operand));
}

std::string runProgram(long long regA, long long regB, long long regC, std::vector<long long> & program)
{   
    std::string output;
    long long instructionPosition = 0;
    while (instructionPosition < program.size())
    {
        bool jumped = false;
        long long operand = program[instructionPosition + 1];
        switch(program[instructionPosition])
        {
            case 0:
                adv(regA, regB, regC, operand);
                break;
            case 1:
                bxl(regA, regB, regC, operand);
                break;

            case 2:
                bst(regA, regB, regC, operand);
                break;

            case 3:
                jumped = jnz(regA, regB, regC, operand, instructionPosition);
                break;

            case 4:
                bxc(regA, regB, regC, operand);
                break;

            case 5:
                output += out(regA, regB, regC, operand) + ',';
                break;

            case 6:
                bdv(regA, regB, regC, operand);
                break;

            case 7:
                cdv(regA, regB, regC, operand);
                break;
        }

        if (!jumped) { instructionPosition += 2; }
    }
    return output.substr(0, output.size() - 1);
}

std::string part1(const std::vector<std::string> & input) 
{
    std::string result;
    std::string registerA = "Register A: ", registerB = "Register B: ", registerC = "Register C: ";
    long long regA = std::stoi(input[0].substr(registerA.size() - 1, input[0].find('\n')));
    long long regB = std::stoi(input[0].substr(input[0].find(registerB) + registerB.size() - 1, input[0].find('\n', input[0].find(registerB)) - registerB.size() - 1));
    long long regC = std::stoi(input[0].substr(input[0].find(registerC) + registerC.size() - 1, input[0].find('\n', input[0].find(registerC)) - registerC.size() - 1));
    std::vector<long long> program = StringParser::toLongLongVector(input[1].substr(std::string("Program: ").size()), ",");
    result = runProgram(regA, regB, regC, program);
    return result;
}

long long getLowestInitialValue(long long regA, int depth, std::vector<long long> program)
{
    if (depth < 0) 
    { 
        return regA; 
    }

    for (int i = 0; i < 8; i++)
    {
        long long a = regA << 3 | i;
        std::vector<long long> output = StringParser::toLongLongVector(runProgram(a, 0, 0, program), ",");
        
        if(output[0] == program[depth]) {
            long long regA = getLowestInitialValue(a, depth - 1, program);
            if (regA != -1)
            {
                return regA;
            }
        }
    }
    return -1;
}

long long part2(const std::vector<std::string> & input) 
{
    long long result = 0;

    std::string registerA = "Register A: ", registerB = "Register B: ", registerC = "Register C: ";
    long long regA = std::stoi(input[0].substr(registerA.size() - 1, input[0].find('\n')));
    long long regB = std::stoi(input[0].substr(input[0].find(registerB) + registerB.size() - 1, input[0].find('\n', input[0].find(registerB)) - registerB.size() - 1));
    long long regC = std::stoi(input[0].substr(input[0].find(registerC) + registerC.size() - 1, input[0].find('\n', input[0].find(registerC)) - registerC.size() - 1));
    std::string programStr = input[1].substr(std::string("Program: ").size());
    std::vector<long long> program = StringParser::toLongLongVector(programStr, ",");
    
    result = getLowestInitialValue(0, program.size() - 1, program);
    assert(programStr == runProgram(result, 0, 0, program));

    return result;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day17_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");
    assert(part1(testinput) == "4,6,3,5,6,3,5,2,1,0");

    FileHandler fileHandler("input-files/2024/day17.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    FileHandler testFileHandler2("input-files/2024/day17_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n\n");
    assert(part2(testinput2) == 117440);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}