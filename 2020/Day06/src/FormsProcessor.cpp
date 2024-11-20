#include "FormsProcessor.hpp"

#include <iostream>
#include <vector>

std::vector<std::string> FormsProcessor::parseGroup(std::string group) {
    std::vector<std::string> personsInGroup;
    std::string person;

    for (char c : group) {
        if (c == '\n') {
            personsInGroup.push_back(person);
            person = "";
        }
        else {
            person += c;
        }
    }
    personsInGroup.push_back(person);

    return personsInGroup;
}

int FormsProcessor::processGroup(std::string groupAnswers, bool combined) {
    std::vector<std::string> personsInGroup = parseGroup(groupAnswers);


    if (combined) {
        std::vector<char> combinedAnswers(personsInGroup[0].begin(), personsInGroup[0].end());
        if (personsInGroup.size() > 1) {
            for (int i = 1; i < personsInGroup.size(); i++) {
                std::vector<char> tmp = combinedAnswers;
                for (char c : combinedAnswers) {
                    if (personsInGroup[i].find(c) == std::string::npos) {
                        tmp.erase(std::find(tmp.begin(), tmp.end(), c));
                    }
                }
                combinedAnswers = tmp;
            }
        }
        return combinedAnswers.size();
    }
    std::vector<char> separateAnswers;
    for (std::string groupPersonAnswers : personsInGroup) {
        for (char answer : groupPersonAnswers) {
            if (std::find(separateAnswers.begin(), separateAnswers.end(), answer) == separateAnswers.end()) {
                separateAnswers.push_back(answer);
            }
        }
    }

    return separateAnswers.size();
}