#include <iostream>
#include <cassert>
#include <chrono>

#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <algorithm>
#include <set>

#include "FileHandler.hpp"
#include "StringParser.hpp"

std::vector<std::string> getOperationsInOrder(std::vector<std::string> unorderedOperations, std::set<std::string> knownValues)
{
    std::vector<std::string> orderedOperations;
    auto it = unorderedOperations.begin();
    while (!unorderedOperations.empty())
    {
        if (it == unorderedOperations.end()) { it = unorderedOperations.begin(); }
    
        std::string lhs = (*it).substr(0, 3);
        std::string rhs = (*it).substr((*it).find('-') - 4, 3);
        if (knownValues.find(lhs) != knownValues.end() && knownValues.find(rhs) != knownValues.end())
        {
            std::string result = (*it).substr((*it).size() - 3);
            orderedOperations.push_back(*it);
            knownValues.insert(result);
            unorderedOperations.erase(it);
            it = unorderedOperations.begin();
        }
        else
        {
            it++;
        }
    }
    return orderedOperations;
}

void executeOperations(const std::vector<std::string> & orderedOperations, std::map<std::string, int> & registers)
{
    for (const std::string & operation : orderedOperations)
    {
        std::string lhs = operation.substr(0, 3);
        std::string operator_ = operation.substr(4, 3);
        std::string rhs = operation.substr(operation.find('-') - 4, 3);
        std::string result = operation.substr(operation.size() - 3);
        if (operator_ == "XOR")
        {
            registers[result] = registers[lhs] ^ registers[rhs];
        }
        else if (operator_ == "OR ")
        {
            registers[result] = registers[lhs] | registers[rhs];
        }
        else if (operator_ == "AND")
        {
            registers[result] = registers[lhs] & registers[rhs];
        }
    }
}

std::string getResult(std::map<std::string, int> registers)
{
    std::string result;
    for (int i = 0; i < 50; i++)
    {
        std::string currentRegister = "z" + ((i < 10) ? "0" + std::to_string(i) : std::to_string(i));
        if (registers.find(currentRegister) != registers.end())
        {
            result = std::to_string(registers[currentRegister]) + result;
        }
        else
        {
            break;
        }
    }
    return result;
}

long long part1(const std::vector<std::string> & input) 
{
    long long result = 0;
    std::vector<std::string> inputStartValues = StringParser::toVector(input[0], "\n");
    std::vector<std::string> inputOperations = StringParser::toVector(input[1], "\n");

    std::map<std::string, int> registers; 
    std::set<std::string> knownValues;
    for (const std::string & register_ : inputStartValues)
    {
        knownValues.insert(register_.substr(0, 3));
        registers[register_.substr(0, 3)] = std::stoi(register_.substr(register_.size() - 1));
    }

    std::vector<std::string> orderedOperations = getOperationsInOrder(inputOperations, knownValues);
    executeOperations(orderedOperations, registers);
    result = std::stoll(getResult(registers), nullptr, 2);

    return result;
}

class RippleAdderVerifier {
public:
    bool verify(int num, std::map<std::string, std::tuple<std::string, std::string, std::string>> & operations)
    {
        std::string z = "z" + ((num < 10) ? "0" + std::to_string(num) : std::to_string(num));
        return verifyZ(z, num, operations);
    }

    bool verifyZ(std::string output, int zNum, std::map<std::string, std::tuple<std::string, std::string, std::string>> & operations)
    {
        std::string lhs = std::get<0>(operations[output]);
        std::string rhs = std::get<1>(operations[output]);
        std::string operator_ = std::get<2>(operations[output]);

        if (operator_ == "XOR")
        {
            if (zNum == 0)
            {
                return (lhs == "x00" && rhs == "y00") || (lhs == "y00" && rhs == "x00");
            }
            return (verifyIntermediateXor(lhs, zNum, operations) && verifyCarryBit(rhs, zNum, operations)) || (verifyIntermediateXor(rhs, zNum, operations) && verifyCarryBit(lhs, zNum, operations));
        }
        return false;
    }

    bool verifyIntermediateXor(std::string output, int zNum, std::map<std::string, std::tuple<std::string, std::string, std::string>> & operations)
    {
        std::string lhs = std::get<0>(operations[output]);
        std::string rhs = std::get<1>(operations[output]);
        std::string operator_ = std::get<2>(operations[output]);

        if (operator_ == "XOR")
        {
            std::string x = "x" + ((zNum < 10) ? "0" + std::to_string(zNum) : std::to_string(zNum));
            std::string y = "y" + ((zNum < 10) ? "0" + std::to_string(zNum) : std::to_string(zNum));
            return (lhs == x && rhs == y) || (lhs == y && rhs == x);
        }
        return false;
    }

    bool verifyCarryBit(std::string output, int zNum, std::map<std::string, std::tuple<std::string, std::string, std::string>> & operations)
    {
        std::string lhs = std::get<0>(operations[output]);
        std::string rhs = std::get<1>(operations[output]);
        std::string operator_ = std::get<2>(operations[output]);
        
        if (zNum == 1)
        {
            std::string x = "x" + ((zNum < 10) ? "0" + std::to_string(zNum) : std::to_string(zNum));
            std::string y = "y" + ((zNum < 10) ? "0" + std::to_string(zNum) : std::to_string(zNum));
            return ((lhs == "x00" && rhs == "y00") || (lhs == "y00" && rhs == "x00")) && (operator_ == "AND");
        }
        if (operator_ == "OR ")
        {
            return (verifyDirectCarry(lhs, zNum - 1, operations) && verifyReCarry(rhs, zNum - 1, operations)) || (verifyDirectCarry(rhs, zNum - 1, operations) && verifyReCarry(lhs, zNum - 1, operations));
        }
        
        return false;
    }

    bool verifyDirectCarry(std::string output, int zNum, std::map<std::string, std::tuple<std::string, std::string, std::string>> & operations)
    {
        std::string lhs = std::get<0>(operations[output]);
        std::string rhs = std::get<1>(operations[output]);
        std::string operator_ = std::get<2>(operations[output]);
        if (operator_ == "AND")
        {
            std::string x = "x" + ((zNum < 10) ? "0" + std::to_string(zNum) : std::to_string(zNum));
            std::string y = "y" + ((zNum < 10) ? "0" + std::to_string(zNum) : std::to_string(zNum));
            return (lhs == x && rhs == y) || (lhs == y && rhs == x);
        }
        return false;
    }
    
    bool verifyReCarry(std::string output, int zNum, std::map<std::string, std::tuple<std::string, std::string, std::string>> & operations)
    {
        std::string lhs = std::get<0>(operations[output]);
        std::string rhs = std::get<1>(operations[output]);
        std::string operator_ = std::get<2>(operations[output]);
        if (operator_ == "AND")
        {
            return (verifyIntermediateXor(lhs, zNum, operations) && verifyCarryBit(rhs, zNum, operations)) || (verifyIntermediateXor(rhs, zNum, operations) && verifyCarryBit(lhs, zNum, operations));
        }
        return false;
    }
};

std::string part2(const std::vector<std::string> & input) 
{
    std::vector<std::string> result;
    std::vector<std::string> inputStartValues = StringParser::toVector(input[0], "\n");
    std::vector<std::string> inputOperations = StringParser::toVector(input[1], "\n");
    
    std::map<std::string, std::tuple<std::string, std::string, std::string>> operations; // key: output, value: lhs, rhs, operator
    for (const std::string & operation : inputOperations)
    {
        std::string lhs = operation.substr(0, 3);
        std::string operator_ = operation.substr(4, 3);
        std::string rhs = operation.substr(operation.find('-') - 4, 3);
        std::string output = operation.substr(operation.size() - 3);
        operations[output] = make_tuple(lhs, rhs, operator_);
    }

    std::vector<std::string> allOutputs;
    for (const auto & operation : operations)
    {
        allOutputs.push_back(operation.first);
    }
    
    // the code represents a ripple carry adder, therefore verify if the instructions follow ripple carry adder rules
    RippleAdderVerifier verifier;
    for (int i = 0; i < (inputStartValues.size()/2); i++)
    {
        if (!verifier.verify(i, operations))
        {
            bool successfulSwap = false;
            // swap until it succeeds
            for (int j = 0; j < allOutputs.size(); j++)
            {
                for (int k = 0; k < allOutputs.size(); k++)
                {
                    if (j == k) { continue; }
                    std::tuple<std::string, std::string, std::string> tmp = operations[allOutputs[j]];
                    operations[allOutputs[j]] = operations[allOutputs[k]];
                    operations[allOutputs[k]] = tmp;
                    if (verifier.verify(i, operations))
                    {
                        result.push_back(allOutputs[j]);
                        result.push_back(allOutputs[k]);
                        successfulSwap = true;
                        break;
                    }
                    // swap back
                    operations[allOutputs[k]] = operations[allOutputs[j]];
                    operations[allOutputs[j]] = tmp;
                }
                if (successfulSwap)
                {
                    break;
                }
            }
        }
    }
    
    std::sort(result.begin(), result.end());
    std::string answer;
    for (const std::string & _register : result)
    {
        answer += _register + ',';
    }
    answer = answer.substr(0, answer.size() - 1);
    return answer;
}

int main(void) 
{
    FileHandler testFileHandler("input-files/2024/day24_testinput1.txt");
    std::vector<std::string> testinput = StringParser::toVector(testFileHandler.getBuffer(), "\n\n");

    assert(part1(testinput) == 4);

    FileHandler testFileHandler2("input-files/2024/day24_testinput2.txt");
    std::vector<std::string> testinput2 = StringParser::toVector(testFileHandler2.getBuffer(), "\n\n");

    assert(part1(testinput2) == 2024);

    FileHandler fileHandler("input-files/2024/day24.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 24, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 24, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}