#pragma once

#include <string>

class FormsProcessor {
private:
    std::vector<std::string> parseGroup(std::string group);
public:
    int processGroup(std::string groupAnswers, bool combined);
};