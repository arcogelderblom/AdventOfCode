#include "BoardingPassScanner.hpp"

#include <iostream>
#include <vector>

int BoardingPassScanner::getSeatId(std::string boardingPass) {
    std::string rowString, columnString;
    int i = 0;
    while(boardingPass[i] != 'L' && boardingPass[i] != 'R') {
        rowString += boardingPass[i] == 'F' ? "0" : "1";
        i++;
    }
    
    std::string totalColumnsString;
    for (int j = boardingPass.length() - i; j > 0; j--) {
        totalColumnsString += "1";
    }

    while(i < boardingPass.length()) {
        columnString += boardingPass[i] == 'L' ? "0" : "1";
        i++;
    }

    int row = std::stoi(rowString, 0, 2);
    int column = std::stoi(columnString, 0, 2);
    int totalColumns = std::stoi(totalColumnsString, 0, 2) + 1;
    return row * totalColumns + column;
}