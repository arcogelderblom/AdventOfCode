#include "ImageProcessor.hpp"

#include <iostream>

ImageProcessor::ImageProcessor(ImageTile image) :
    _image(image)
{}

int ImageProcessor::findSeaMonsters() {
    // sea monster its offsets
    //                   #
    // #    ##    ##    ###
    //  #  #  #  #  #  #
    std::vector< std::pair<int, int> > seaMonsterOffsets = {
            {0, 18},
            {1,0}, {1,5}, {1,6}, {1,11}, {1,12}, {1,17},{1,18}, {1,19},
            {2,1}, {2,4}, {2,7}, {2,10}, {2,13}, {2,16}};
    int seaMonsterMaxRowOffset = 2;
    int seaMonsterMaxColumnOffset = 19;

    int seaMonstersFound = 0;
    std::vector<std::string> & array = _image.getArray();
    for (int row = 0; row < array.size() - seaMonsterMaxRowOffset; row++) {
        for (int column = 0; column < array.size() - seaMonsterMaxColumnOffset; column++) {
            bool seaMonsterFound = true;
            for (std::pair<int, int> seaMonsterOffset : seaMonsterOffsets) {
                if (array[row + seaMonsterOffset.first][column + seaMonsterOffset.second] != '#') {
                    seaMonsterFound = false;
                    break;
                }
            }
            if (seaMonsterFound) {
                for (std::pair<int, int> seaMonsterOffset : seaMonsterOffsets) {
                    array[row + seaMonsterOffset.first][column + seaMonsterOffset.second] = 'O';
                }
                seaMonstersFound++;
            }
        }
    }
    return seaMonstersFound;
}

int ImageProcessor::getRoughWaters() {
    for (int side = 0; side < 4; side++) {
        if (findSeaMonsters() != 0) {
            break;
        }

        _image.flipArrayLeftRight();
        if (findSeaMonsters() != 0) {
            break;
        }
        _image.flipArrayLeftRight(); // flip back

        _image.flipArrayTopBottom();
        if (findSeaMonsters() != 0) {
            break;
        }
        _image.flipArrayTopBottom(); // flip back

        _image.rotateArrayRight();
    }

    const std::vector<std::string> array = _image.getArray();
    int roughWaters = 0;
    for (int row = 0; row < array.size(); row++) {
        for (int column = 0; column < array.size(); column++) {
            if (array[row][column] == '#') {
                roughWaters++;
            }
        }
    }

    return roughWaters;
}
