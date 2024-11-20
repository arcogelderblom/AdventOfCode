#include <iostream>

#include <sstream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "MessageProcessor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day19.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
    std::vector<std::string> rules, messages;
    
    std::stringstream ssRules(input[0]);
    std::string rule;
    while(std::getline(ssRules,rule)){
        rules.push_back(rule);
    }

    std::stringstream ssMessages(input[1]);
    std::string message;
    while(std::getline(ssMessages,message)){
        messages.push_back(message);
    }
    MessageProcessor processor(rules);
    std::cout << "Puzzle one output: " << processor.getMatchingMessages(messages, 0, false).size() << std::endl;

    FileHandler fileHandler2("input-files/2020/day19_2.txt");
    std::vector<std::string> input2 = StringParser::toVector(fileHandler2.getBuffer(), "\n\n");
    
    std::stringstream ssRules2(input2[0]);
    rules = std::vector<std::string>();
    while(std::getline(ssRules2,rule)){
        rules.push_back(rule);
    }

    std::stringstream ssMessages2(input2[1]);
    messages = std::vector<std::string>();
    while(std::getline(ssMessages2,message)){
        messages.push_back(message);
    }
    MessageProcessor processor2(rules);
    std::cout << "Puzzle two output: " << processor2.getMatchingMessages(messages, 0, true).size() << std::endl;
    // for (std::string msg : processor2.getMatchingMessages(messages, 0)) {
    //     std::cout << msg << std::endl;
    // }
}
