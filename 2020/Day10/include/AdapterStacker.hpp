#pragma once

#include <string>
#include <vector>

class AdapterStacker {
private:
    std::vector<int> _adapterJolts;
    void parse(std::vector<std::string> adapterJolts);
public:
    AdapterStacker(std::vector<std::string> adapterJolts);
    int getAmountDifference(int joltsDifference);
    long getAmountOfOptions();
};