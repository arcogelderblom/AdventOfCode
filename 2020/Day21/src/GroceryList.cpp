#include "GroceryList.hpp"

#include <iostream>

GroceryList::GroceryList(std::vector<std::string> products) {
    for (std::string product : products) {
        _list.push_back(Product(product));
    }
}

void GroceryList::determineAllergens() {
    std::map<std::string, std::vector<std::string> > allergenWithOptions;
    for (Product currentProduct : _list) {
        std::vector<std::string> knownAllergens = currentProduct.getKnownAllergens();
        for (std::string allergen : knownAllergens) {
            std::vector<Product> productsWithAllergen;
            for (Product product : _list) {
                if (product != currentProduct) {
                    std::vector<std::string> productKnownAllergens = product.getKnownAllergens();
                    if (std::find(productKnownAllergens.begin(), productKnownAllergens.end(), allergen) != productKnownAllergens.end()) {
                        productsWithAllergen.push_back(product);
                    }
                }
            }

            for (std::string ingredient : currentProduct.getIngredients()) {
                bool allProductsHoldIngredient = true;
                for (Product product : productsWithAllergen) {
                    std::vector<std::string> productsIngredients = product.getIngredients();
                    if (std::find(productsIngredients.begin(), productsIngredients.end(), ingredient) == productsIngredients.end()) {
                        allProductsHoldIngredient = false;
                    }
                }
                if (allProductsHoldIngredient) {
                    if (std::find(allergenWithOptions[allergen].begin(), allergenWithOptions[allergen].end(), ingredient) == allergenWithOptions[allergen].end()) {
                        allergenWithOptions[allergen].push_back(ingredient);
                    }
                }
            }
        }
    }

    // determine which ingredient is which allergen
    while (allergenWithOptions.size() > 0) {
        std::vector<std::string> foundAllergens;
        for (std::pair<std::string, std::vector<std::string> > allergenWithOption : allergenWithOptions) {
            if (allergenWithOption.second.size() == 1) {
                _allergens[allergenWithOption.first] = allergenWithOption.second[0];
                foundAllergens.push_back(allergenWithOption.first);
            }
        }
        for (std::string foundAllergen : foundAllergens) {
            allergenWithOptions.erase(foundAllergen);
            for (auto & option : allergenWithOptions) {
                if (std::find(option.second.begin(), option.second.end(), _allergens[foundAllergen]) != option.second.end()) {
                    option.second.erase(std::find(option.second.begin(), option.second.end(), _allergens[foundAllergen]));
                }
            }
        }
    }
}

int GroceryList::getAmountOfNonAllergensInProducts() {
    determineAllergens();
    int result = 0;
    for (Product product : _list) {
        std::vector<std::string> ingredients = product.getIngredients();
        for (std::string ingredient : product.getIngredients()) {
            bool isAllergen = false;
            for (std::pair<std::string, std::string> allergen : _allergens) {
                if (allergen.second == ingredient) {
                    isAllergen = true;
                }
            }
            if (!isAllergen) {
                result += 1;
            }
        }
    }
    return result;
}

std::string GroceryList::getCanonicalDangerousIngredientList() {
    std::string result;
    for (std::pair<std::string, std::string> allergenWithIngredient : _allergens) {
        result += allergenWithIngredient.second;
        result += ',';
    }
    return std::string(result.begin(), result.end() - 1);
}

