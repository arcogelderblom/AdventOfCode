#pragma once

#include <vector>
#include <map>

#include "Product.hpp"

class GroceryList {
private:
    std::vector<Product> _list;
    std::map<std::string, std::string> _allergens;
    void determineAllergens();
public:
    GroceryList(std::vector<std::string> products);
    int getAmountOfNonAllergensInProducts();
    std::string getCanonicalDangerousIngredientList();
};
