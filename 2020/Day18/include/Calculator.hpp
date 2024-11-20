#pragma once

#include <string>
#include <vector>

class Calculator {
    std::string _expression;
    long solveV1(std::string expressionWithoutParentheses);
    long solveV2(std::string expressionWithoutParentheses);
public:
    Calculator(std::string expression);
    long getAnswer(int puzzle);
};