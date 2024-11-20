#include "AdapterStacker.hpp"

#include <numeric>

AdapterStacker::AdapterStacker(std::vector<std::string> adapterJolts) {
    parse(adapterJolts);
}

void AdapterStacker::parse(std::vector<std::string> adapterJolts) {
    for (std::string jolts : adapterJolts) {
        _adapterJolts.push_back(std::stoi(jolts));
    }
    std::sort(_adapterJolts.begin(), _adapterJolts.end());
    // add wall adapter
    _adapterJolts.insert(_adapterJolts.begin(), 0);
    // add own device
    _adapterJolts.push_back(_adapterJolts[_adapterJolts.size() - 1] + 3);
}

int AdapterStacker::getAmountDifference(int joltsDifference) {
    int amount = 0;
    for (int i = 0; i+1 <= _adapterJolts.size(); i++) {
        if (_adapterJolts[i+1] - _adapterJolts[i] == joltsDifference) {
            amount++;
        }
    }
    return amount;
}

long AdapterStacker::getAmountOfOptions() {
    std::vector<long> optionsPerJolt;
    optionsPerJolt.resize(_adapterJolts.back() + 3);
    optionsPerJolt[2] = 1;
    for (int jolt : _adapterJolts) {
        // calculate options how to get to certain jolt
        if (jolt == 0) {
            continue;
        }
        optionsPerJolt[jolt + 2] = optionsPerJolt[jolt - 1] + optionsPerJolt[jolt] + optionsPerJolt[jolt + 1];
    }
    return optionsPerJolt.back();
}
