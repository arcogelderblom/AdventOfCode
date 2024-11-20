#pragma once

#include <string>
#include <vector>

class FloorPlan {
private:
    std::vector<std::string> & _floorPlan;
    bool playRoundPuzzleOne();
    bool playRoundPuzzleTwo();
    int countAdjecentSeatsOccupied(int row, int column);
    int countVisibleSeatsOccupied(int row, int column);
public:
    FloorPlan(std::vector<std::string> & floorPlan);
    int getOccupiedSeatsAmount(int puzzle);
};