#include <iostream>

#include "FloorPlan.hpp"

int main(void) {
    std::vector<std::string> input = {"L.LL.LL.LL",
                                      "LLLLLLL.LL",
                                      "L.L.L..L..",
                                      "LLLL.LL.LL",
                                      "L.LL.LL.LL",
                                      "L.LLLLL.LL",
                                      "..L.L.....",
                                      "LLLLLLLLLL",
                                      "L.LLLLLL.L",
                                      "L.LLLLL.LL"};
    std::vector<std::string> input2 = {"L.LL.LL.LL",
                                      "LLLLLLL.LL",
                                      "L.L.L..L..",
                                      "LLLL.LL.LL",
                                      "L.LL.LL.LL",
                                      "L.LLLLL.LL",
                                      "..L.L.....",
                                      "LLLLLLLLLL",
                                      "L.LLLLLL.L",
                                      "L.LLLLL.LL"};

    FloorPlan floorPlan(input);
    std::cout << "Puzzle one output: " << floorPlan.getOccupiedSeatsAmount(1) << std::endl;
    
    FloorPlan floorPlan2(input2);
    std::cout << "Puzzle two output: " << floorPlan2.getOccupiedSeatsAmount(2) << std::endl;
}
