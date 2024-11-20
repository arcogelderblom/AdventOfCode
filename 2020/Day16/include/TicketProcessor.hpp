#pragma once

#include <string>
#include <vector>
#include <map>

class TicketProcessor {
private:
    std::vector<std::string> _rules;
    std::map< std::string, std::vector<int> > _rulesWithValues;
    std::map<std::string, int> _rulesPerField;
    std::vector<int> _validNumbers;
    void calculateValidNumbers();
    void parseRules();
public:
    TicketProcessor(std::vector<std::string> rules);
    int getTicketScanningErrorRate(std::vector< std::vector<int> > tickets);
    void determineFields(std::vector< std::vector<int> > tickets);
    long getMultiplicationDeparture(std::vector<int> ticket);
};