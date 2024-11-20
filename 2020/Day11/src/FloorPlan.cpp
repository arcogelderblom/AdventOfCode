#include "FloorPlan.hpp"

FloorPlan::FloorPlan(std::vector<std::string> & floorPlan) :
    _floorPlan(floorPlan)
{}

int FloorPlan::getOccupiedSeatsAmount(int puzzle) {
    if (puzzle == 1) {
        while(playRoundPuzzleOne());
    }
    if (puzzle == 2) {
        while(playRoundPuzzleTwo());
    }

    int count = 0;
    for (std::string row : _floorPlan) {
        for (char seat : row) {
            if (seat == '#') {
                count++;
            }
        }
    }
    return count;
}

bool FloorPlan::playRoundPuzzleOne() {
    std::vector<std::string> newFloorPlan;
    bool changed = false;
    for (int row = 0; row < _floorPlan.size(); row++) {
        std::string newRow;
        for (int column = 0; column < _floorPlan[row].length(); column++) {
            switch(_floorPlan[row][column]) {
                case '.':
                    newRow += '.';
                    break;
                case 'L':
                    if (countAdjecentSeatsOccupied(row, column) == 0) {
                        newRow += '#';
                        changed = true;
                    }
                    else {
                        newRow += 'L';
                    }
                    break;
                case '#':
                    if (countAdjecentSeatsOccupied(row, column) >= 4) {
                        newRow += 'L';
                        changed = true;
                    }
                    else {
                        newRow += '#';
                    }
                    break;
            }
        }
        newFloorPlan.push_back(newRow);
    }
    _floorPlan = newFloorPlan;
    return changed;
}

bool FloorPlan::playRoundPuzzleTwo() {
    std::vector<std::string> newFloorPlan;
    bool changed = false;
    for (int row = 0; row < _floorPlan.size(); row++) {
        std::string newRow;
        for (int column = 0; column < _floorPlan[row].length(); column++) {
            switch(_floorPlan[row][column]) {
                case '.':
                    newRow += '.';
                    break;
                case 'L':
                    if (countVisibleSeatsOccupied(row, column) == 0) {
                        newRow += '#';
                        changed = true;
                    }
                    else {
                        newRow += 'L';
                    }
                    break;
                case '#':
                    if (countVisibleSeatsOccupied(row, column) >= 5) {
                        newRow += 'L';
                        changed = true;
                    }
                    else {
                        newRow += '#';
                    }
                    break;
            }
        }
        newFloorPlan.push_back(newRow);
    }
    _floorPlan = newFloorPlan;
    return changed;
}

int FloorPlan::countAdjecentSeatsOccupied(int row, int column) {
    int occupiedSeats = 0;
    std::vector<std::pair<int, int>> coordinates {{-1, -1}, {0, -1}, {1, -1},
                                                  {-1, 0}, {0, 0}, {1, 0},
                                                  {-1, 1}, {0, 1}, {1, 1}};
    for (std::pair<int, int> coordinate : coordinates) {
        if (coordinate == std::pair<int, int>{0,0}) {
            continue;
        }
        if (row+coordinate.first < 0 || column+coordinate.second < 0) {
            continue;
        }
        if (_floorPlan[row+coordinate.first][column+coordinate.second] == '#') {
            occupiedSeats++;
        }
    }

    return occupiedSeats;
}

int FloorPlan::countVisibleSeatsOccupied(int row, int column) {
    int occupiedSeats = 0;
    std::vector<std::pair<int, int>> coordinates {{-1, -1}, {0, -1}, {1, -1},
                                                  {-1, 0}, {0, 0}, {1, 0},
                                                  {-1, 1}, {0, 1}, {1, 1}};
    for (std::pair<int, int> coordinate : coordinates) {
        int currentRow = row;
        int currentColumn = column;
        char current = '.';
        while (current == '.') {
            if (coordinate == std::pair<int, int>{0,0}) {
                break;
            }
            currentRow += coordinate.first;
            currentColumn += coordinate.second;

            if (currentRow < 0 || currentColumn < 0) {
                break;
            }
            current = _floorPlan[currentRow][currentColumn];
        }
        if (current == '#') {
            occupiedSeats++;
        }
    }

    return occupiedSeats;
}