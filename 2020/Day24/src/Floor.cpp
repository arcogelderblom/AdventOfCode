#include "Floor.hpp"

#include "HexTileCoordinate.hpp"

Floor::Floor(const std::vector<std::string> & instructions) {
    HexTile startingTile(_startingCoordinate);
    _floor[_startingCoordinate] = startingTile;
    for (const std::string & instruction : instructions) {
        applyInstruction(instruction);
    }
}

void Floor::applyInstruction(std::string instruction) {
    HexTile * currentTile = &_floor[_startingCoordinate];
    while (!instruction.empty()) {
        // get current instruction
        std::string currentInstruction;
        if (instruction[0] == 'e' || instruction[0] == 'w') {
            currentInstruction = instruction.substr(0, 1);
            instruction = std::string(instruction.begin() + 1, instruction.end());
        }
        else {
            currentInstruction = instruction.substr(0, 2);
            instruction = std::string(instruction.begin() + 2, instruction.end());
        }
        HexTileCoordinate newCoordinate = currentTile->getCoordinate();
        if (currentInstruction == "e") {
            if (currentTile->e == nullptr) {
                newCoordinate._q += 1;
                newCoordinate._s -= 1;
                if (_floor.find(newCoordinate) == _floor.end()) {
                    HexTile newTile(newCoordinate);
                    _floor[newCoordinate] = newTile;
                }
                currentTile->e = &_floor[newCoordinate];
            }
            currentTile = currentTile->e;
        }
        else if (currentInstruction == "se") {
            if (currentTile->se == nullptr) {
                newCoordinate._r += 1;
                newCoordinate._s -= 1;
                if (_floor.find(newCoordinate) == _floor.end()) {
                    HexTile newTile(newCoordinate);
                    _floor[newCoordinate] = newTile;
                }
                currentTile->se = &_floor[newCoordinate];
            }
            currentTile = currentTile->se;
        }
        else if (currentInstruction == "sw") {
            if (currentTile->sw == nullptr) {
                newCoordinate._q -= 1;
                newCoordinate._r += 1;
                if (_floor.find(newCoordinate) == _floor.end()) {
                    HexTile newTile(newCoordinate);
                    _floor[newCoordinate] = newTile;
                }
                currentTile->sw = &_floor[newCoordinate];
            }
            currentTile = currentTile->sw;
        }
        else if (currentInstruction == "w") {
            if (currentTile->w == nullptr) {
                newCoordinate._q -= 1;
                newCoordinate._s += 1;
                if (_floor.find(newCoordinate) == _floor.end()) {
                    HexTile newTile(newCoordinate);
                    _floor[newCoordinate] = newTile;
                }
                currentTile->w = &_floor[newCoordinate];
            }
            currentTile = currentTile->w;
        }
        else if (currentInstruction == "nw") {
            if (currentTile->nw == nullptr) {
                newCoordinate._r -= 1;
                newCoordinate._s += 1;
                if (_floor.find(newCoordinate) == _floor.end()) {
                    HexTile newTile(newCoordinate);
                    _floor[newCoordinate] = newTile;
                }
                currentTile->nw = &_floor[newCoordinate];
            }
            currentTile = currentTile->nw;
        }
        else if (currentInstruction == "ne") {
            if (currentTile->ne == nullptr) {
                newCoordinate._q += 1;
                newCoordinate._r -= 1;
                if (_floor.find(newCoordinate) == _floor.end()) {
                    HexTile newTile(newCoordinate);
                    _floor[newCoordinate] = newTile;
                }
                currentTile->ne = &_floor[newCoordinate];
            }
            currentTile = currentTile->ne;
        }
    }
    currentTile->flip();
}

void Floor::processDays(int days) {
    for (int day = 1; day <= days; day++) {
        std::map<HexTileCoordinate, HexTile> newFloor;
        for (std::pair<HexTileCoordinate, HexTile> coordinate : _floor) {
            HexTile currentTile = _floor[coordinate.first];
            checkAdjacentTiles(currentTile, newFloor);
        }
        _floor = newFloor;
    }
}

void Floor::checkAdjacentTiles(HexTile currentTile, std::map<HexTileCoordinate, HexTile> & newFloor, int depth) {
    int maxDepth = 1;
    if (depth > maxDepth) {
        return; // maxDepth reached
    }

    HexTileCoordinate newCoordinate = currentTile.getCoordinate();
    if (newFloor.find(newCoordinate) != newFloor.end()) {
        return; // this tile is already tried
    }

    HexTileCoordinate e = newCoordinate;
    e._q += 1;
    e._s -= 1;
    HexTileCoordinate se = newCoordinate;
    se._r += 1;
    se._s -= 1;
    HexTileCoordinate sw = newCoordinate;
    sw._q -= 1;
    sw._r += 1;
    HexTileCoordinate w = newCoordinate;
    w._q -= 1;
    w._s += 1;
    HexTileCoordinate nw = newCoordinate;
    nw._r -= 1;
    nw._s += 1;
    HexTileCoordinate ne = newCoordinate;
    ne._q += 1;
    ne._r -= 1;

    std::vector<TileColor> neighbouringColors;
    std::vector<HexTileCoordinate> neighbours = {e, se, sw, w, nw, ne};
    for (HexTileCoordinate coordinate : neighbours) {
        if (_floor.find(coordinate) == _floor.end()) {
            HexTile newTile(coordinate);
            checkAdjacentTiles(newTile, newFloor, depth+1);
            neighbouringColors.push_back(TileColor::White);
        }
        else {
            neighbouringColors.push_back(_floor[coordinate].getColor());
        }
    }

    int amountBlack = std::count_if(neighbouringColors.begin(), neighbouringColors.end(), [](TileColor tileColor){ return tileColor == TileColor::Black; });
    if (currentTile.getColor() == TileColor::Black && (amountBlack == 0 || amountBlack > 2)) {
        currentTile.flip();
    }
    else if (currentTile.getColor() == TileColor::White && amountBlack == 2) {
        currentTile.flip();
    }

    if (currentTile.getColor() == TileColor::Black) {
        newFloor[currentTile.getCoordinate()] = currentTile;
    }
    else {
        newFloor.erase(currentTile.getCoordinate());
    }
}

std::vector<HexTile*> Floor::getBlackTiles() {
    std::vector<HexTile*> result;
    for (std::pair<HexTileCoordinate, HexTile> coordinateTilePair : _floor) {
        if (coordinateTilePair.second.getColor() == TileColor::Black) {
            result.push_back(&coordinateTilePair.second);
        }
    }
    return result;
}
