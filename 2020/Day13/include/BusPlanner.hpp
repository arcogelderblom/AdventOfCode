#pragma once

#include <string>
#include <vector>
#include <map>

class BusPlanner {
private:
    std::vector<int> _busses;
    bool validateTimestamp(long long timestamp, std::map<int, int> busIdWithDelta);
public:
    BusPlanner(std::string busIds);
    long puzzleOne(int minutes);
    long long puzzleTwo();
};