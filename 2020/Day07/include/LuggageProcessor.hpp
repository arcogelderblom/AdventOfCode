#pragma once

#include <vector>
#include "Bag.hpp"

class LuggageProcessor {
private:
    std::vector<Bag> _bags;
    void parse(std::string bag);
public:
    LuggageProcessor(std::vector<std::string> bags);
    int getColorPossibilitiesFor(std::string color);
    int getAmountBagsInBag(std::string color);
};