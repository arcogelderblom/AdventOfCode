#include <iostream>
#include <cassert>
#include <vector>

#include "BoardingPassScanner.hpp"

int main(void) {
    std::vector<std::string> input = {"BFFFBBFRRR",
                                      "FFFBBBFRRR",
                                      "BBFFBBFRLL"};
    
    BoardingPassScanner scanner;
    int highestSeatId = 0;
    for (std::string boardingPass : input) {
        int id = scanner.getSeatId(boardingPass);
        if (id > highestSeatId) {
            highestSeatId = id;
        }
    }

    assert(highestSeatId == 820);
}
