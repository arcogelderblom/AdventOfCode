#pragma once

#include <map>
#include <vector>
#include <string>

#include "HexTileCoordinate.hpp"
#include "HexTile.hpp"

class Floor {
private:
    HexTileCoordinate _startingCoordinate{0, 0, 0};
    std::map<HexTileCoordinate, HexTile> _floor;
    void applyInstruction(std::string instruction);
    void checkAdjacentTiles(HexTile currentTile, std::map<HexTileCoordinate, HexTile> & newFloor, int depth = 0);
public:
    Floor(const std::vector<std::string> & instructions);
    void processDays(int days);
    std::vector<HexTile*> getBlackTiles();
};