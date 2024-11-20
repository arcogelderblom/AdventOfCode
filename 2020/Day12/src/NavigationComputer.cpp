#include "NavigationComputer.hpp"

#include <iostream>

NavigationComputer::NavigationComputer(std::vector<std::string> route) :
    _shipX(0),
    _shipY(0),
    _waypointX(10),
    _waypointY(1),
    _route(route)
{}

void NavigationComputer::navigate() {
    _shipX = 0;
    _shipY = 0;
    char currentDirection = 'E';
    for (std::string instruction : _route) {
        switch (instruction[0]) {
            case 'N':
            case 'E':
            case 'S':
            case 'W':
                move(instruction[0], std::stoi(instruction.substr(1)));
                break;
            case 'L':
            case 'R':
                currentDirection = turn(currentDirection, instruction[0], std::stoi(instruction.substr(1)));
                break;
            case 'F':
                move(currentDirection, std::stoi(instruction.substr(1)));
                break;
        }
    }
}

void NavigationComputer::navigatePuzzle2() {
    _shipX = 0;
    _shipY = 0;
    _waypointX = 10;
    _waypointY = 1;
    for (std::string instruction : _route) {
        int units = std::stoi(instruction.substr(1));
        switch (instruction[0]) {
            case 'N':
            case 'E':
            case 'S':
            case 'W':
                moveWaypoint(instruction[0], units);
                break;
            case 'L':
            case 'R':
                turnWaypoint(instruction[0], units);
                break;
            case 'F':
                _shipX += _waypointX*units;
                _shipY += _waypointY*units;
                break;
        }
    }
}


void NavigationComputer::move(char direction, int units) {
    switch (direction) {
        case 'N':
            _shipY += units;
            break;
        case 'E':
            _shipX += units;
            break;
        case 'S':
            _shipY -= units;
            break;
        case 'W':
            _shipX -= units;
            break;
    }
}

void NavigationComputer::moveWaypoint(char direction, int units) {
    switch (direction) {
        case 'N':
            _waypointY += units;
            break;
        case 'E':
            _waypointX += units;
            break;
        case 'S':
            _waypointY -= units;
            break;
        case 'W':
            _waypointX -= units;
            break;
    }
}

char NavigationComputer::turn(char currentDirection, char side, int degrees) {
    std::vector<char> directions = {'N', 'E', 'S', 'W'};
    if (degrees == 180) {
        auto it = std::find(directions.begin(), directions.end(), currentDirection);
        if (*it == 'N' || *it == 'E') {
            return *(it+2);
        }
        return *(it-2);
    }
    if (side == 'R' && degrees == 90) {
        return turn(currentDirection, 'L', 270);
    }
    if (side == 'R' && degrees == 270) {
        return turn(currentDirection, 'L', 90);
    }
    if (side == 'L' && degrees == 90) {
        auto it = std::find(directions.begin(), directions.end(), currentDirection);
        if (*it == 'N') {
            return 'W';
        }
        else {
            return *(it-1);
        }
    }
    if (side == 'L' && degrees == 270) {
        auto it = std::find(directions.begin(), directions.end(), currentDirection);
        if (*it == 'W') {
            return 'N';
        }
        else {
            return *(it+1);
        }
    }
    return ' ';
}

void NavigationComputer::turnWaypoint(char side, int degrees) {
    if (side == 'R') {
        for (int angle = 0; angle < degrees; angle+=90) {
            _waypointX = -_waypointX;
            std::swap(_waypointX, _waypointY);
        }
    }
    else {
        for (int angle = 0; angle < degrees; angle+=90) {
            _waypointY = -_waypointY;
            std::swap(_waypointX, _waypointY);
        }
    }
}

int NavigationComputer::getManhattanDistance(int puzzle) {
    if (puzzle == 1) {
        navigate();
    }
    else if (puzzle == 2) {
        navigatePuzzle2();
    }
    return std::abs(_shipX) + std::abs(_shipY);
}
