#include "ConwayCubesV2.hpp"

ConwayCubesV2::ConwayCubesV2(std::vector<std::string> conwayCubes) {
    int fourthDimension = 0;
    int slice = 0;
    int row = 0;
    for (std::string cubeRow : conwayCubes) {
        int column = 0;
        for (char c : cubeRow) {
            if (c == '#') {
                CubeV2 cube;
                cube.x = column;
                cube.y = row;
                cube.z = slice;
                cube.w = fourthDimension;
                cube.active = true;
                _cubes.push_back(cube);
            }
            column++;
        }
        row++;
    }
}

void ConwayCubesV2::cycle(int amountOfCycles) {
    for (int cycle = 0; cycle < amountOfCycles; cycle++) {
        std::vector<CubeV2> newCubes;
        std::pair<int, int> xBounds = calculateBounds('x');
        std::pair<int, int> yBounds = calculateBounds('y');
        std::pair<int, int> zBounds = calculateBounds('z');
        std::pair<int, int> wBounds = calculateBounds('w');
        xBounds.first -= 1;
        xBounds.second += 1;
        yBounds.first -= 1;
        yBounds.second += 1;
        zBounds.first -= 1;
        zBounds.second += 1;
        wBounds.first -= 1;
        wBounds.second += 1;

        for (int w = wBounds.first; w <= wBounds.second; w++) {
            for (int z = zBounds.first; z <= zBounds.second; z++) {
                for (int y = yBounds.first; y <= yBounds.second; y++) {
                    for (int x = xBounds.first; x <= xBounds.second; x++) {
                        bool currentCubeState = false;
                        for (CubeV2 cube : _cubes) {
                            if (cube.x == x && cube.y == y && cube.z == z && cube.w == w) {
                                currentCubeState = cube.active;
                                break;
                            }
                        }

                        std::vector<CubeV2> neighbours;
                        for (int wNeighbour = w-1; wNeighbour <= w+1; wNeighbour++) {
                            for (int zNeighbour = z-1; zNeighbour <= z+1; zNeighbour++) {
                                for (int yNeighbour = y-1; yNeighbour <= y+1; yNeighbour++) {
                                    for (int xNeighbour = x-1; xNeighbour <= x+1; xNeighbour++) {
                                        if (xNeighbour == x && yNeighbour == y && zNeighbour == z && wNeighbour == w) {
                                            continue;
                                        }
                                        CubeV2 neighbourCube;
                                        neighbourCube.x = xNeighbour;
                                        neighbourCube.y = yNeighbour;
                                        neighbourCube.z = zNeighbour;
                                        neighbourCube.w = wNeighbour;
                                        if (xNeighbour < xBounds.first || xNeighbour > xBounds.second ||
                                            yNeighbour < yBounds.first || yNeighbour > yBounds.second ||
                                            zNeighbour < zBounds.first || zNeighbour > zBounds.second ||
                                            wNeighbour < wBounds.first || wNeighbour > wBounds.second) {
                                            neighbourCube.active = false;
                                        }
                                        else {
                                            bool neighbourCubeState = false;
                                            for (CubeV2 cube : _cubes) {
                                                if (cube.x == xNeighbour && cube.y == yNeighbour && cube.z == zNeighbour && cube.w == wNeighbour) {
                                                    neighbourCubeState = cube.active;
                                                    break;
                                                }
                                            }
                                            neighbourCube.active = neighbourCubeState;
                                        }
                                        neighbours.push_back(neighbourCube);
                                    }
                                }
                            }
                        }

                        int activeNeighbours = 0;
                        for (CubeV2 neighbour : neighbours) {
                            if (neighbour.active) {
                                activeNeighbours++;
                            }
                        }

                        bool newState = false;
                        if (currentCubeState) {
                            if (activeNeighbours == 2 || activeNeighbours == 3) {
                                newState = true;
                            }
                        }
                        else {
                            if (activeNeighbours == 3) {
                                newState = true;
                            }
                        }

                        if (newState == true) {
                            CubeV2 cube;
                            cube.x = x;
                            cube.y = y;
                            cube.z = z;
                            cube.w = w;
                            cube.active = newState;
                            newCubes.push_back(cube);
                        }
                    }   
                }
            }
        }
        _cubes = newCubes;
    }
}

std::pair<int, int> ConwayCubesV2::calculateBounds(char axis) {
    std::pair<int, int> bounds = std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
    if (axis == 'x') {
        for (CubeV2 cube : _cubes) {
            if (cube.x < bounds.first) {
                bounds.first = cube.x;
            }
            if (cube.x > bounds.second) {
                bounds.second = cube.x;
            }
        }
    }
    if (axis == 'y') {
        for (CubeV2 cube : _cubes) {
            if (cube.y < bounds.first) {
                bounds.first = cube.y;
            }
            if (cube.y > bounds.second) {
                bounds.second = cube.y;
            }
        }
    }
    if (axis == 'z') {
        for (CubeV2 cube : _cubes) {
            if (cube.z < bounds.first) {
                bounds.first = cube.z;
            }
            if (cube.z > bounds.second) {
                bounds.second = cube.z;
            }
        }
    }
    if (axis == 'w') {
        for (CubeV2 cube : _cubes) {
            if (cube.w < bounds.first) {
                bounds.first = cube.w;
            }
            if (cube.w > bounds.second) {
                bounds.second = cube.w;
            }
        }
    }

    return bounds;
}

int ConwayCubesV2::getActiveCubes() {
    int activeCubes = 0;
    for (CubeV2 cube : _cubes) {
        if (cube.active) {
            activeCubes++;
        }
    }
    return activeCubes;
}