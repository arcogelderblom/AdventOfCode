#include <iostream>

#include "CupGame.hpp"

int main(void) {
    std::string input = "716892543";
    CupGame cupGame(input, input.size());
    std::cout << "Puzzle one output: " << cupGame.getResultAfterRounds(100) << std::endl;

    CupGame cupGame2(input, 1000000);
    std::vector<Cup*> cupsWithStar = cupGame2.getStarCups(10000000);
    std::cout << "Puzzle two output: " << static_cast<long>(cupsWithStar[0]->getNum()) * static_cast<long>(cupsWithStar[1]->getNum()) << std::endl;
}
