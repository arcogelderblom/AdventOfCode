#pragma once

#include <vector>
#include <string>

class Product {
private:
    std::vector<std::string> _ingredients;
    std::vector<std::string> _knownAllergens;
public:
    Product(std::string ingredientsAndAllergens);
    std::vector<std::string> getIngredients();
    std::vector<std::string> getKnownAllergens();

    friend bool operator==(const Product& lhs, const Product& rhs)
    {
        return lhs._knownAllergens == rhs._knownAllergens && lhs._ingredients == rhs._ingredients;
    }

    friend bool operator!=(const Product& lhs, const Product& rhs)
    {
        return !(lhs == rhs);
    }
};