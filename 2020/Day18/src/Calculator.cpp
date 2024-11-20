#include "Calculator.hpp"

Calculator::Calculator(std::string expression) :
    _expression(expression)
{}

long Calculator::getAnswer(int puzzle) {
    std::vector<int> startingParenthesesIndex;
    auto closingParentheses = _expression.find(')');
    while (closingParentheses != std::string::npos) {
        auto startingParentheses = _expression.rfind('(', closingParentheses);
        std::string expressionWithinParentheses = _expression.substr(startingParentheses+1, closingParentheses-startingParentheses-1);
        long parenthesesSolution = 0;
        if (puzzle == 1) {
            parenthesesSolution = solveV1(expressionWithinParentheses);
        }
        else if (puzzle == 2) {
            parenthesesSolution = solveV2(expressionWithinParentheses);
        }
        _expression = _expression.replace(startingParentheses, closingParentheses-startingParentheses+1, std::to_string(parenthesesSolution));

        closingParentheses = _expression.find(')');
    }

    if (puzzle == 1) {
        return solveV1(_expression);
    }
    return solveV2(_expression);
}

long Calculator::solveV1(std::string expressionWithoutParentheses) {
    long result = 0;

    std::string lValue = expressionWithoutParentheses.substr(0, expressionWithoutParentheses.find(' '));
    expressionWithoutParentheses = expressionWithoutParentheses.substr(expressionWithoutParentheses.find(' ') + 1);
    while (expressionWithoutParentheses.size() > 0) {
        std::string operatorInExpression = expressionWithoutParentheses.substr(0, expressionWithoutParentheses.find(' '));
        expressionWithoutParentheses = expressionWithoutParentheses.substr(expressionWithoutParentheses.find(' ') + 1);
        std::string rValue = expressionWithoutParentheses.substr(0, expressionWithoutParentheses.find(' '));
        if (expressionWithoutParentheses == rValue) {
            expressionWithoutParentheses = "";
        }
        else {
            expressionWithoutParentheses = expressionWithoutParentheses.substr(expressionWithoutParentheses.find(' ') + 1);
        }
        
        if (operatorInExpression == "+") {
            result = std::stol(lValue) + std::stol(rValue); 
        }
        else if (operatorInExpression == "*") {
            result = std::stol(lValue) * std::stol(rValue); 
        }
        lValue = std::string(std::to_string(result));
    }
    return result;
} 


long Calculator::solveV2(std::string expressionWithoutParentheses) {
    if (expressionWithoutParentheses.find(" * ") == std::string::npos) {
        return solveV1(expressionWithoutParentheses);
    }
    auto plusOperator = expressionWithoutParentheses.find(" + ");
    while(plusOperator != std::string::npos) {
        auto start = expressionWithoutParentheses.rfind(' ', plusOperator - 1);
        if (start == std::string::npos) {
            start = 0;
        }
        else {
            start += 1;
        }
        auto end = expressionWithoutParentheses.find(' ', plusOperator + std::string(" + ").size());
        long solution = solveV1(expressionWithoutParentheses.substr(start, end-start));
        expressionWithoutParentheses = expressionWithoutParentheses.replace(start, end-start, std::to_string(solution));
        plusOperator = expressionWithoutParentheses.find(" + ");
    }
    return solveV1(expressionWithoutParentheses);
} 
