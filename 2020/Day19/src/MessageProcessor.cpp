#include "MessageProcessor.hpp"

MessageProcessor::MessageProcessor(std::vector<std::string> rules) {
    for (std::string rule : rules) {
        std::string rulNum = rule.substr(0, rule.find(':'));
        _rules[std::stoi(rulNum)] = rule.substr(rule.find(' ') + 1);
    }
}

std::vector<std::string> MessageProcessor::getMatchingMessages(std::vector<std::string> messages, int rule, bool part2) {
    _part2 = part2;
    std::vector<std::string> matchingMessages;
    for (std::string message : messages) {
        int currentMessageIndex = 0;
        if (getMatch(message, currentMessageIndex, rule)) {
            if (currentMessageIndex == message.size() - 1) {
                matchingMessages.push_back(message);
            }
        }
    }
    return matchingMessages;
}
bool MessageProcessor::getMatch(std::string message, int & currentMessageIndex, int currentRuleIndex, int maxDepth, int currentDepth) {
    if (_rules[currentRuleIndex] == "\"a\"" || _rules[currentRuleIndex] == "\"b\"") {
        char c = _rules[currentRuleIndex][1];
        return message[currentMessageIndex] == c;
    }

    if (_rules[currentRuleIndex].find('|') != std::string::npos) {
        // 2 alternatives
        std::vector<int> firstAlternativeOptions = parseMultipleOptions(_rules[currentRuleIndex].substr(0, _rules[currentRuleIndex].find(" | ")));
        int messageIndexFirstAlternative = currentMessageIndex;
        std::vector<bool> resultsFirstAlternative = getResult(message, firstAlternativeOptions, messageIndexFirstAlternative, maxDepth, currentDepth);

        std::vector<int> secondAlternativeOptions = parseMultipleOptions(_rules[currentRuleIndex].substr(_rules[currentRuleIndex].find(" | ") + 3));
        int messageIndexSecondAlternative = currentMessageIndex;
        std::vector<bool> resultsSecondAlternative = getResult(message, secondAlternativeOptions, messageIndexSecondAlternative, maxDepth, currentDepth);

        if (std::find(resultsSecondAlternative.begin(), resultsSecondAlternative.end(), false) == resultsSecondAlternative.end()) {
            currentMessageIndex = messageIndexSecondAlternative;
            return true;
        }
        if (std::find(resultsFirstAlternative.begin(), resultsFirstAlternative.end(), false) == resultsFirstAlternative.end()) {
            currentMessageIndex = messageIndexFirstAlternative;
            return true;
        }
        return false;
    }

    std::vector<int> optionsRuleNum = parseMultipleOptions(_rules[currentRuleIndex]);
    int msgIndex = currentMessageIndex;
    std::vector<bool> results;
    if (_part2) {
        if (currentDepth == 0) {
            while (maxDepth < message.size() - 1) {
                msgIndex = 0;
                results = getResult(message, optionsRuleNum, msgIndex, ++maxDepth, currentDepth + 1);
                if (std::find(results.begin(), results.end(), false) == results.end()) {
                    currentMessageIndex = msgIndex;
                    return true;
                }
            }
            return false;
        };
        results = getResult(message, optionsRuleNum, msgIndex, maxDepth, currentDepth);
    }
    else {
        results = getResult(message, optionsRuleNum, msgIndex);
    }

    if (std::find(results.begin(), results.end(), false) == results.end()) {
        currentMessageIndex = msgIndex;
        return true;
    }
    return false;
}

std::vector<int> MessageProcessor::parseMultipleOptions(std::string options) {
    std::vector<int> optionsRuleNums;
    while (options.find(' ') != std::string::npos) {
        int optionRuleNum = std::stoi(options.substr(0, options.find(' ')));
        optionsRuleNums.push_back(optionRuleNum);
        options = options.substr(options.find(' ') + 1);
    }
    optionsRuleNums.push_back(std::stoi(options));
    return optionsRuleNums;
}

std::vector<bool> MessageProcessor::getResult(std::string message, std::vector<int> options, int & currentMessageIndex, int maxDepth, int currentDepth) {
    if (_part2) {
        if (options.size() >= 2) {
            if (options.at(1) == 8) {
                if (currentDepth >= maxDepth) {
                    return std::vector<bool>{false};
                }
                else {
                    currentDepth++;
                }
            } else if (options.size() == 3) {
                if (options.at(1) == 11 && options.at(2) == 31) {
                    if (currentMessageIndex >= message.size()) {
                        return std::vector<bool>{false};
                    }
                }
            }
        }
    }
    std::vector<bool> results;
    for (const int ruleIndex : options) {
        if (_part2) {
            results.push_back(getMatch(message, currentMessageIndex, ruleIndex, maxDepth, currentDepth));
        }
        else {
            results.push_back(getMatch(message, currentMessageIndex, ruleIndex));
        }

        currentMessageIndex++;
    }
    currentMessageIndex--;
    return results;
}
