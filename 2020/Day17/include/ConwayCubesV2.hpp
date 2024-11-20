#pragma once

#include <string>
#include <vector>

struct CubeV2 {
    int x;
    int y;
    int z;
    int w;
    bool active = false;
};

class ConwayCubesV2 {
private:
    std::vector<CubeV2> _cubes;
    std::pair<int, int> calculateBounds(char axis);
public:
    ConwayCubesV2(std::vector<std::string> conwayCubes);
    void cycle(int amountOfCycles);
    int getActiveCubes();
};