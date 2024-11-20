#pragma once

#include <string>
#include <vector>
#include <map>

class MessageProcessor {
    std::map<int, std::string> _rules;
    bool _part2 = false;
    bool getMatch(std::string message, int & currentMessageIndex, int currentRuleIndex, int maxDepth = 0, int currentDepth = 0);
    std::vector<bool> getResult(std::string message, std::vector<int> options, int & currentMessageIndex, int maxDepth = 0, int currentDepth = 0);
    std::vector<int> parseMultipleOptions(std::string options);
public:
    MessageProcessor(std::vector<std::string> rules);
    std::vector<std::string> getMatchingMessages(std::vector<std::string> messages, int rule, bool part2);
};