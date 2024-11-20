#include "TicketProcessor.hpp"

#include <iostream>

TicketProcessor::TicketProcessor(std::vector<std::string> rules) :
    _rules(rules)
{
    calculateValidNumbers();
    parseRules();
}

void TicketProcessor::calculateValidNumbers() {
    for (std::string rule : _rules) {
        std::string values = rule.substr(rule.find(": ") + 2);
        std::string firstPair = values.substr(0, values.find(" or "));
        std::string secondPair = values.substr(values.find(" or ") + 4);
        std::pair<int, int> firstValues = std::make_pair(std::stoi(firstPair.substr(0, firstPair.find('-'))), std::stoi(firstPair.substr(firstPair.find('-')+1)));
        std::pair<int, int> secondValues = std::make_pair(std::stoi(secondPair.substr(0, secondPair.find('-'))), std::stoi(secondPair.substr(secondPair.find('-')+1)));
        for (int num = firstValues.first; num <= firstValues.second; num++) {
            if (std::find(_validNumbers.begin(), _validNumbers.end(), num) == _validNumbers.end()) {
                _validNumbers.push_back(num);
            }
        }
        for (int num = secondValues.first; num <= secondValues.second; num++) {
            if (std::find(_validNumbers.begin(), _validNumbers.end(), num) == _validNumbers.end()) {
                _validNumbers.push_back(num);
            }
        }
    }
}

void TicketProcessor::parseRules() {
    for (std::string rule : _rules) {
        std::string currentRule = rule.substr(0, rule.find(": "));
        std::string values = rule.substr(rule.find(": ") + 2);
        std::string firstPair = values.substr(0, values.find(" or "));
        std::string secondPair = values.substr(values.find(" or ") + 4);
        std::pair<int, int> firstValues = std::make_pair(std::stoi(firstPair.substr(0, firstPair.find('-'))), std::stoi(firstPair.substr(firstPair.find('-')+1)));
        std::pair<int, int> secondValues = std::make_pair(std::stoi(secondPair.substr(0, secondPair.find('-'))), std::stoi(secondPair.substr(secondPair.find('-')+1)));
        std::vector<int> validNumbers;

        for (int num = firstValues.first; num <= firstValues.second; num++) {
            validNumbers.push_back(num);
        }
        for (int num = secondValues.first; num <= secondValues.second; num++) {
            validNumbers.push_back(num);
        }

        _rulesWithValues[currentRule] = validNumbers;
    }
}

int TicketProcessor::getTicketScanningErrorRate(std::vector< std::vector<int> > tickets) {
    int errorRate = 0;
    for (std::vector<int> ticket : tickets) {
        for(int fieldValue : ticket) {
            if (fieldValue > *(_validNumbers.end() - 1) / 2) { // guess the half the fieldValue is in to get answer faster 
                if (std::find(_validNumbers.rbegin(), _validNumbers.rend(), fieldValue) == _validNumbers.rend()) {
                    errorRate += fieldValue;
                }
            }
            else {
                if (std::find(_validNumbers.begin(), _validNumbers.end(), fieldValue) == _validNumbers.end()) {
                    errorRate += fieldValue;
                }
            }
        }
    }
    return errorRate;
}

void TicketProcessor::determineFields(std::vector< std::vector<int> > tickets) {
    std::vector< std::vector<int> > validTickets;
    
    for (std::vector<int> ticket : tickets) {
        bool validTicket = true;
        for (int fieldValue : ticket) {
            if (std::find(_validNumbers.begin(), _validNumbers.end(), fieldValue) == _validNumbers.end()) {
                validTicket = false;
                break;
            }
        }
        if (validTicket) {
            validTickets.push_back(ticket);
        }
    }
    std::map< std::string, std::vector<int> > optionsPerField;
    for (std::pair< std::string, std::vector<int> > field : _rulesWithValues) {
        int fieldIndex = 0;
        for (int i = 0; i < validTickets.size(); i++) {
            if (std::find(field.second.begin(), field.second.end(), validTickets[i][fieldIndex]) == field.second.end()) {
                i = -1; // i++ is after loop so ensure it starts at 0
                fieldIndex += 1;
            }
            else {
                if (i == validTickets.size() - 1) {
                    optionsPerField[field.first].push_back(fieldIndex);
                    if (fieldIndex < validTickets[0].size()) {
                        fieldIndex += 1;
                        i = -1;
                    }
                }
            }

            if (fieldIndex == validTickets[0].size()) {
                break;
            }
        }
    }

    while (optionsPerField.size() > 0) {
        // get a item with 1 value only
        for (std::pair<std::string, std::vector<int>> optionPerField : optionsPerField) {
            if (optionPerField.second.size() == 1) {
                // only one option for this field
                _rulesPerField[optionPerField.first] = optionPerField.second[0];
                for (auto & option : optionsPerField) {
                    if (std::find(option.second.begin(), option.second.end(), optionPerField.second[0]) != option.second.end() && option.first != optionPerField.first) {
                        option.second.erase(std::find(option.second.begin(), option.second.end(), optionPerField.second[0]));
                    }
                }
                
                optionsPerField.erase(optionPerField.first);
                break;
            }
        }
    }
}

long TicketProcessor::getMultiplicationDeparture(std::vector<int> ticket) {
    long total = 1;
    for (std::pair<std::string, int> rulePerField : _rulesPerField) {
        if (rulePerField.first.find("departure") != std::string::npos) {
            total *= ticket[rulePerField.second];
        }
    }
    return total;
}
