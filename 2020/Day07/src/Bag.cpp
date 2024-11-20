#include "Bag.hpp"

Bag::Bag(std::string bagColor,  std::vector<std::pair<Bag, int>> containingBags) :
    _bagColor(bagColor),
    _containingBags(containingBags)
{}

std::vector<std::pair<Bag, int>>& Bag::getContainingBags() {
    return _containingBags;
}

std::string Bag::getColor() {
    return _bagColor;
}