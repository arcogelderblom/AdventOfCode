#include "Product.hpp"

#include <iostream>

Product::Product(std::string ingredientsAndAllergens) {
    std::string ingredientsString = ingredientsAndAllergens.substr(0, ingredientsAndAllergens.find('(') - 1);
    std::string allergensString = ingredientsAndAllergens.substr(ingredientsAndAllergens.find('('));
    allergensString = std::string(allergensString.begin() + 10, allergensString.end() - 1); // begin + 10 to strip '(contains '
    while (ingredientsString.find(' ') != std::string::npos) {
        int index = ingredientsString.find(' ');
        _ingredients.push_back(ingredientsString.substr(0, index));
        ingredientsString = ingredientsString.substr(index + 1);
    }
    _ingredients.push_back(ingredientsString);

    while (allergensString.find(", ") != std::string::npos) {
        int index = allergensString.find(", ");
        _knownAllergens.push_back(allergensString.substr(0, index));
        allergensString = allergensString.substr(index + 2);
    }
    _knownAllergens.push_back(allergensString);
}

std::vector<std::string> Product::getIngredients() {
    return _ingredients;
}

std::vector<std::string> Product::getKnownAllergens() {
    return _knownAllergens;
}
