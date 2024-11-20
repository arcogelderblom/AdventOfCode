#include "HexTile.hpp"

HexTile::HexTile(HexTileCoordinate coordinate) :
    _coordinate(coordinate)
{}


HexTile::HexTile(const HexTile& copy) :
    _coordinate(copy._coordinate),
    _color(copy._color)
{}

void HexTile::flip() {
    if (getColor() == White) {
        _color = Black;
    }
    else {
        _color = White;
    }
}

HexTileCoordinate HexTile::getCoordinate() {
    return _coordinate;
}

TileColor HexTile::getColor() {
    return _color;
}