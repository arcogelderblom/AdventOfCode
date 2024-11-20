#pragma once

#include <string>
#include <vector>

class NavigationComputer {
private:
    int _shipX;
    int _shipY;
    int _waypointX;
    int _waypointY;
    std::vector<std::string> _route;
    void navigate();
    void navigatePuzzle2();
    void move(char direction, int units);
    void moveWaypoint(char direction, int units);
    char turn(char currentDirection, char side, int degrees);
    void turnWaypoint(char side, int degrees);
public:
    NavigationComputer(std::vector<std::string> route);
    int getManhattanDistance(int puzzle);
};