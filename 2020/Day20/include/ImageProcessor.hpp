#pragma once

#include "ImageTile.hpp"

class ImageProcessor {
private:
    ImageTile _image;
    int findSeaMonsters();
public:
    ImageProcessor(ImageTile image);
    int getRoughWaters();
};