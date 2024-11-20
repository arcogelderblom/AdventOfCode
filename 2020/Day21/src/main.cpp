#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "GroceryList.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day21.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    GroceryList groceryList(input);
    std::cout << "Puzzle one output: " << groceryList.getAmountOfNonAllergensInProducts() << std::endl;
    std::cout << "Puzzle two output: " << groceryList.getCanonicalDangerousIngredientList() << std::endl;
}
