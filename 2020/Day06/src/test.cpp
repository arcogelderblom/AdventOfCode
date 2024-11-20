#include <iostream>
#include <cassert>

#include <vector>
#include "FormsProcessor.hpp"

int main(void) {
    std::vector<std::string> input {"abc", "a\nb\nc", "ab\nac", "a\na\na\na", "b"};
    
    FormsProcessor processor;
    int sum = 0;
    for (std::string groupAnswers : input) {
        sum += processor.processGroup(groupAnswers, false);
    }

    assert(sum == 11);

    sum = 0;
    for (std::string groupAnswers : input) {
        sum += processor.processGroup(groupAnswers, true);
    }
    
    assert(sum == 6);
}