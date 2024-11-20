#pragma once

#include "HexTileCoordinate.hpp"

enum TileColor {
    White = 0,
    Black = 1
};

class HexTile {
private:
    HexTileCoordinate _coordinate;
    TileColor _color = TileColor::White;
public:
    HexTile * e = nullptr;
    HexTile * se = nullptr;
    HexTile * sw = nullptr;
    HexTile * w = nullptr;
    HexTile * nw = nullptr;
    HexTile * ne = nullptr;

    HexTile(HexTileCoordinate coordinate = HexTileCoordinate{0, 0, 0});
    HexTile(const HexTile& copy);
    void flip();
    HexTileCoordinate getCoordinate();
    TileColor getColor();
};