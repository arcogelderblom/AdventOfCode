#include "LuggageProcessor.hpp"

#include <iostream>

LuggageProcessor::LuggageProcessor(std::vector<std::string> bags) {
    for (std::string bag : bags) {
        parse(bag);
    }
    // processBags();
}

void LuggageProcessor::parse(std::string bag) {
    std::string color = bag.substr(0, bag.find(" bags"));
    std::string containingBagsString = bag.substr(bag.find("contain ") + std::string("contain ").size());
    
    if (containingBagsString == "no other bags.") {
        _bags.push_back(Bag(color,  std::vector<std::pair<Bag, int>>()));
    }
    else {
        std::vector<std::string> bags;
        while(containingBagsString.find(',') != std::string::npos) {
            bags.push_back(containingBagsString.substr(0, containingBagsString.find(',')));
            containingBagsString = containingBagsString.substr(containingBagsString.find(',') + 2);
        }
        bags.push_back(containingBagsString);

        std::vector<std::pair<Bag, int>> containingBags;
        for (std::string b : bags) {
            int amount = std::stoi(b.substr(0, b.find(' ')));
            Bag containingBag = Bag(b.substr(b.find(' ') + 1, b.find(" bag") - b.find(' ') - 1),  std::vector<std::pair<Bag, int>>());
            containingBags.push_back(std::make_pair(containingBag, amount));
        }
        _bags.push_back(Bag(color, containingBags));
    }
}

int LuggageProcessor::getColorPossibilitiesFor(std::string color) {
    std::vector<Bag> result;

    std::vector<Bag> bagsContainingColor;
    for (Bag bag : _bags) {
        std::vector<std::pair<Bag, int>> containingBags = bag.getContainingBags();
        for (std::pair<Bag, int> containedBag : containingBags) {
            if (containedBag.first.getColor() == color) {
                if (std::find_if(bagsContainingColor.begin(), bagsContainingColor.end(), [&bag](Bag other){ return bag.getColor() == other.getColor();}) == bagsContainingColor.end()) {
                    bagsContainingColor.push_back(bag);
                    result.push_back(bag);
                }
            }
        }
    }

    bool atTopLevel = false;
    while (!atTopLevel) {
        atTopLevel = true;
        std::vector<Bag> bagsAtLevel = bagsContainingColor;
        bagsContainingColor = std::vector<Bag>();
        for (Bag bagContainingColor : bagsAtLevel) {
            std::string curColor = bagContainingColor.getColor();
            for (Bag bag : _bags) {
                std::vector<std::pair<Bag, int>> containingBags = bag.getContainingBags();
                for (std::pair<Bag, int> containedBag : containingBags) {
                    if (containedBag.first.getColor() == curColor) {
                        if (std::find_if(bagsContainingColor.begin(), bagsContainingColor.end(), [&bag](Bag other){ return bag.getColor() == other.getColor();}) == bagsContainingColor.end()) {
                            bagsContainingColor.push_back(bag);
                            result.push_back(bag);
                        }
                        atTopLevel = false;
                    }
                }
            }
        }
    }

    std::vector<Bag> tmp;
    for (Bag bag : result) {
        if (std::find_if(tmp.begin(), tmp.end(), [&bag](Bag other){ return bag.getColor() == other.getColor();}) == tmp.end()) {
            tmp.push_back(bag);
        }
    }
    result = tmp;

    return result.size();
}

int LuggageProcessor::getAmountBagsInBag(std::string color) {
    int containingBagsAmount = 0;
    for (Bag bag : _bags) {
        if (bag.getColor() == color) {
            if (bag.getContainingBags().empty()) {
                return 0;
            }
            for (std::pair<Bag, int> containingBag : bag.getContainingBags()) {
                containingBagsAmount += containingBag.second;
                containingBagsAmount += containingBag.second * getAmountBagsInBag(containingBag.first.getColor());
            }
        }
    }

    return containingBagsAmount;
}