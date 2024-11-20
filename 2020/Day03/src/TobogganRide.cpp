#include "TobogganRide.hpp"

int TobogganRide::countTrees(std::vector<std::string> map, int slopeRight, int slopeDown) {
    int currentSlopeRight = 0;
    int trees = 0;
    for (int currentSlopeDown = 0; currentSlopeDown < map.size(); currentSlopeDown += slopeDown) {
        if (currentSlopeRight >= map[0].size()) {
            currentSlopeRight -= map[0].size();
        }

        if (map[currentSlopeDown][currentSlopeRight] == '#') {
            trees++;
        } 
        currentSlopeRight += slopeRight;
    }
    return trees;
}