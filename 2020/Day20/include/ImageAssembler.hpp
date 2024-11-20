#pragma once

#include <string>
#include <vector>
#include "ImageTile.hpp"

class ImageAssembler {
private:
    std::vector<ImageTile> _allTiles;
    std::vector< std::vector<ImageTile> > _image;
    void preFillImage();
    ImageTile * match(ImageTile current, int side, ImageTile other);
    ImageTile * matchSide(std::string currentSide, ImageTile & other);
    int getMatchingSide(ImageTile currentTile, ImageTile & otherTile);
public:
    ImageAssembler(std::vector<std::string> imageTiles);
    void assemble();
    std::vector<ImageTile> getCornerTileIds();
    ImageTile getImage();
};