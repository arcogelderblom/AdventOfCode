#pragma once

#include <string>
#include <vector>

class Bag {
private:
    std::string _bagColor;
    std::vector<std::pair<Bag, int>> _containingBags;
public:
    Bag(std::string bagColor,  std::vector<std::pair<Bag, int>> containingBags);
    std::vector<std::pair<Bag, int>>& getContainingBags();
    std::string getColor();

    bool operator<(const Bag& other) const {
        return _bagColor < other._bagColor;
    }

    bool operator==(const Bag& rhs) const
    {
        return (_bagColor == rhs._bagColor)
        && (_containingBags == rhs._containingBags);
    }
};