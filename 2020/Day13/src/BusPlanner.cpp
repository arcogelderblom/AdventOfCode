#include "BusPlanner.hpp"

#include <cmath>
#include <numeric>
#include <iostream>

BusPlanner::BusPlanner(std::string busIds) {
    while (busIds.find(',') != std::string::npos) {
        std::string busIdString = busIds.substr(0, busIds.find(','));
        if (busIdString != "x") {
            _busses.push_back(std::stoi(busIdString));
        }
        else {
            _busses.push_back(0);
        }
        busIds = busIds.substr(busIds.find(',') + 1);
    }
    if (busIds != "x") {
        _busses.push_back(std::stoi(busIds));
    }
    else {
        _busses.push_back(0);
    }
}

long BusPlanner::puzzleOne(int minutes) {
    std::vector<std::pair<int, int>> busIdWithTimeToWait;
    int lowestWaitTime = std::numeric_limits<int>::max();
    int fastestBusId = 0;

    for (int busId : _busses) {
        if (busId != 0) {
            int curMinutes = std::floor(minutes / busId) * busId + busId;
            busIdWithTimeToWait.push_back(std::make_pair(busId, curMinutes));
            if (curMinutes < lowestWaitTime) {
                lowestWaitTime = curMinutes;
                fastestBusId = busId;
            }
        }
    }

    return fastestBusId * (lowestWaitTime - minutes);
}

long long BusPlanner::puzzleTwo() {
    std::map<int, int> busIdWithDelta;
    for (int i = 0; i < _busses.size(); i++) {
        if (_busses[i] != 0) {
            busIdWithDelta[i] = _busses[i];
        }
    }

//    BRUTE FORCE WAY
//    long long startingPoint = 100000000000000;
//    while(startingPoint % busIdWithDelta[0] != 0) {
//        startingPoint++;
//    }
//
//    for (long long currentTimeStamp = startingPoint; ; currentTimeStamp+=busIdWithDelta[0]) {
//        std::cout << currentTimeStamp << std::endl;
//        if (validateTimestamp(currentTimeStamp, busIdWithDelta)) {
//            return currentTimeStamp;
//        }
//    }

//  CHINESE REMAINDER THEOREM
    long long sum = 0;
    long long modulus = 1;
    for (std::pair<int, int> pair : busIdWithDelta) {
        int delta = pair.first;
        int busId = pair.second;
        modulus *= busId;
        // euclidean algorithm
        long long result = 1;
        for (std::pair<int, int> _ : busIdWithDelta) {
            if (_.second != busId) {
                result *= _.second;
            }
        }

        long long tmpLeft = busId;
        long long tmpRight = result;
        tmpLeft = busId * (tmpRight/busId);
        while ((tmpLeft * -1) + tmpRight != 1 && tmpLeft + (tmpRight*-1) != 1 ) {
            if (tmpRight < tmpLeft) {
                tmpRight += result;
                tmpLeft = busId * (tmpRight/busId);
            }
            tmpLeft += busId;
        }

        if (tmpRight < tmpLeft) {
            tmpRight *= -1;
        }
        sum += ((delta == 0) ? 0 : busId - delta) * tmpRight;
    }

    return (sum % modulus + modulus) % modulus;
}

bool BusPlanner::validateTimestamp(long long int timestamp, std::map<int, int> busIdWithDelta) {
    for (std::pair<int, int> busIdAndDelta : busIdWithDelta) {
        if (((timestamp + busIdAndDelta.first) % busIdAndDelta.second) != 0) {
            return false;
        }
    }
    return true;
}
