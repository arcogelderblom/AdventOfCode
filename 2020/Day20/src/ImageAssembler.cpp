#include "ImageAssembler.hpp"

#include <iostream>
#include <cmath>
#include <map>

ImageAssembler::ImageAssembler(std::vector<std::string> imageTiles) {
    for (std::string imageTile : imageTiles) {
        ImageTile tile(imageTile);
        _allTiles.push_back(tile);
    }
}

void ImageAssembler::preFillImage() {
    int imageDimensions = sqrt(_allTiles.size());
    std::vector<ImageTile> row;
    for (int i = 0; i < imageDimensions; i++) {
        ImageTile placeholder;
        row.push_back(placeholder);
    }

    for (int i = 0; i < imageDimensions; i++) {
        _image.push_back(row);
    }
};

ImageTile * ImageAssembler::match(ImageTile current, int side, ImageTile other) {
    // return ImageTile other as it is (rotated if necessary, to match the current's side)
    ImageTile * matchedTile = nullptr;
    std::vector<std::string> currentArray = current.getArray();
    std::string currentSide = "";
    switch(side) {
        case 0: // top or bottom
            for (int i = 0; i < 4; i++) {
                currentArray = current.getArray();
                currentSide = currentArray[0];
                matchedTile = matchSide(currentSide, other);
                if (matchedTile != nullptr) {
                    matchedTile->rotateArrayRight();
                    matchedTile->rotateArrayRight();
                    break;
                }
                current.rotateArrayRight();
            }
            break;
        case 1: // right or left
            for (int i = 0; i < 4; i++) {
                currentArray = current.getArray();
                currentSide = "";
                for (int j = currentArray.size() - 1; j >= 0; j--) {
                    currentSide += currentArray[j][currentArray.size()-1];
                }
                matchedTile = matchSide(currentSide, other);
                if (matchedTile != nullptr) {
                    matchedTile->rotateArrayRight();
                    matchedTile->rotateArrayRight();
                    matchedTile->rotateArrayRight();
                    break;
                }
                current.rotateArrayRight();
            }
            break;
    }

    return matchedTile;
}

ImageTile * ImageAssembler::matchSide(std::string currentSide, ImageTile & other) {
    // matches are taken from the top
    ImageTile * result = nullptr;
    for (int side = 0; side < 4; side++) {
        std::string otherSide = other.getArray()[0];
        if (currentSide == otherSide) {
            result = &other;
            return result;
        }
        other.rotateArrayRight();

    }
    return result;
}

int ImageAssembler::getMatchingSide(ImageTile currentTile, ImageTile & otherTile) {
    std::vector<std::string> currentArray = currentTile.getArray();

    // create the strings to match
    std::string topSideForMatch = std::string(currentArray[0].rbegin(), currentArray[0].rend());
    std::string rightSideForMatch = "";
    for (int i = currentArray.size() - 1; i >= 0; i--) {
        rightSideForMatch += currentArray[i][currentArray.size() - 1];
    }
    std::string bottomSideForMatch = currentArray[currentArray.size()-1];
    std::string leftSideForMatch = "";
    for (int i = 0; i < currentArray.size(); i++) {
        leftSideForMatch += currentArray[i][0];
    }

    std::vector<std::string> sides = {topSideForMatch, rightSideForMatch, bottomSideForMatch, leftSideForMatch};
    // returns: 0 = top, 1 = right, 2 = bottom, 3 = left
    for (int sideOfCurrent = 0; sideOfCurrent < 4; sideOfCurrent++) {
        std::string currentSide = sides[sideOfCurrent];
        for (int side = 0; side < 4; side++) {
            std::string otherSide = otherTile.getArray()[0];
            if (currentSide == otherSide) {
                return sideOfCurrent;
            }

            otherTile.flipArrayLeftRight();
            otherSide = otherTile.getArray()[0];
            if (currentSide == otherSide) {
                return sideOfCurrent;
            }
            otherTile.flipArrayLeftRight(); // flip back

            otherTile.flipArrayTopBottom();
            otherSide = otherTile.getArray()[0];
            if (currentSide == otherSide) {
                return sideOfCurrent;
            }
            otherTile.flipArrayTopBottom(); // flip back

            otherTile.rotateArrayRight();
        }
    }
    return -1;
}

void ImageAssembler::assemble() {
    preFillImage();
    // everything without match at one side is a top/left/right/bottom, everything without matches at 2 sides is corner
    std::map<ImageTile, std::vector<ImageTile> > matchingTilesIds;
    for (ImageTile thisTile : _allTiles) {
        for (int side = 0; side < 2; side++) {
            for (ImageTile otherTile : _allTiles) {
                if (otherTile.getTileId() == thisTile.getTileId()) {
                    continue;
                }
                bool result = match(thisTile, side, otherTile);
                if (result) {
                    matchingTilesIds[thisTile].push_back(otherTile);
                }
            }
        }
    }
    long long result = 1;
    for (std::pair<ImageTile, std::vector<ImageTile> > matchingTiles : matchingTilesIds) {
        if (matchingTiles.second.size() == 2) {
            result *= matchingTiles.first.getTileId();
            // start with first corner
            _image[0][0] = matchingTiles.first;
        }
    }

    std::vector<int> matchingSides;
    for (ImageTile matchingTile : matchingTilesIds[_image[0][0]]) {
        matchingSides.push_back(getMatchingSide(_image[0][0], matchingTile));
    }
    if (std::find(matchingSides.begin(), matchingSides.end(), 0) != matchingSides.end()) {
        if (std::find(matchingSides.begin(), matchingSides.end(), 1) != matchingSides.end()) {
            _image[0][0].rotateArrayRight();
        }
        else if (std::find(matchingSides.begin(), matchingSides.end(), 3) != matchingSides.end()) {
            _image[0][0].rotateArrayRight();
            _image[0][0].rotateArrayRight();
        }
    }
    else if (std::find(matchingSides.begin(), matchingSides.end(), 2) != matchingSides.end()) {
        if (std::find(matchingSides.begin(), matchingSides.end(), 1) != matchingSides.end()) {
            // correct rotation for top left corner
        }
        else if (std::find(matchingSides.begin(), matchingSides.end(), 3) != matchingSides.end()) {
            _image[0][0].rotateArrayRight();
            _image[0][0].rotateArrayRight();
            _image[0][0].rotateArrayRight();
        }
    }

    for (int row = 0; row < sqrt(_allTiles.size()); row++) {
        for (int column = 0; column < sqrt(_allTiles.size()); column++) {
            if (column == sqrt(_allTiles.size())-1) {
                // get match from top because we need to create the new row
                ImageTile currentTile = _image[row][0];
                for (ImageTile matchingTile : matchingTilesIds[currentTile]) {
                    if (getMatchingSide(currentTile, matchingTile) == 2) {
                        // since matches are taken from the top this will work
                        _image[row+1][0] = matchingTile;
                    }
                }
            }
            else {
                ImageTile currentTile = _image[row][column];
                for (ImageTile matchingTile : matchingTilesIds[currentTile]) {
                    if (getMatchingSide(currentTile, matchingTile) == 1) {
                        // since matches are taken from the top we need to rotate 3 times
                        matchingTile.rotateArrayRight();
                        matchingTile.rotateArrayRight();
                        matchingTile.rotateArrayRight();
                        _image[row][column+1] = matchingTile;
                    }
                }
            }
        }
    }
}

std::vector<ImageTile> ImageAssembler::getCornerTileIds() {
    std::vector<ImageTile> cornerTiles;
    cornerTiles.push_back(_image[0][0]); // top left
    cornerTiles.push_back(_image[0][_image[0].size()-1]); // top right
    cornerTiles.push_back(_image[_image.size()-1][0]); // bottom left
    cornerTiles.push_back(_image[_image.size()-1][_image[_image.size()-1].size()-1]); // bottom right
    return cornerTiles;
}

ImageTile ImageAssembler::getImage() {
    std::string tileId = "Tile 0:\n";
    std::string imageTileString = tileId;
    for (std::vector<ImageTile> rowTiles : _image) {
        int row = 1;
        while (row < rowTiles[0].getArray().size() - 1) {
            for (ImageTile columnTile : rowTiles) {
                int column = 1;
                while (column < columnTile.getArray()[row].size()-1) {
                    imageTileString += columnTile.getArray()[row][column];
                    column++;
                }
            }
            row++;
            imageTileString += '\n';
        }
    }
    return ImageTile(imageTileString);
}
