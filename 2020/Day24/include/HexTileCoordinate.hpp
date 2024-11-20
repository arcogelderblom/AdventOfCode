#pragma once

#include <tuple>

struct HexTileCoordinate {
    int _q;
    int _r;
    int _s;
    HexTileCoordinate(int q, int r, int s) :
        _q(q),
        _r(r),
        _s(s)
    {}

    friend bool operator<(const HexTileCoordinate& lhs, const HexTileCoordinate& rhs) {
        return std::tie(lhs._q, lhs._r, lhs._s) < std::tie( rhs._q, rhs._r, rhs._s );
    }

    friend bool operator==(const HexTileCoordinate& lhs, const HexTileCoordinate& rhs) {
        return std::tie(lhs._q, lhs._r, lhs._s) == std::tie( rhs._q, rhs._r, rhs._s );
    }
};
