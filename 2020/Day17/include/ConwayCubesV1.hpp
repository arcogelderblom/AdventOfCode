#pragma once

#include <string>
#include <vector>

struct CubeV1 {
    int x;
    int y;
    int z;
    bool active = false;
};

class ConwayCubesV1 {
private:
    std::vector<CubeV1> _cubes;
    std::pair<int, int> calculateBounds(char axis);
public:
    ConwayCubesV1(std::vector<std::string> conwayCubes);
    void cycle(int amountOfCycles);
    int getActiveCubes();
};