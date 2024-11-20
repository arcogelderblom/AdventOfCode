#include "ImageTile.hpp"

#include <iostream>

ImageTile::ImageTile() :
    _tileId(0),
    _array()
{}

ImageTile::ImageTile(std::string idAndArray) {
    std::string idString = idAndArray.substr(0,idAndArray.find(':'));
    idString = idString.substr(idString.find(' ') + 1);
    _tileId = std::stoi(idString);

    std::string arrayString = idAndArray.substr(idAndArray.find('\n') + 1);
    int arraySize = arrayString.find('\n');
    for (int i = 1; i <= idAndArray.size()-arraySize; i++) {
        std::string tileRow = arrayString.substr(i-1,arraySize);
        _array.push_back(tileRow);
        i += arraySize;
    }
}

void ImageTile::rotateArrayRight() {
    std::vector<std::string> arrayAfterRotation;
    int dimension = _array.size();
    for (int row = 0; row < dimension; row++) {
        std::string newRow = "";
        for (int column = dimension - 1; column >= 0; column--) {
            newRow += _array[column][row];
        }
        arrayAfterRotation.push_back(newRow);
    }
    _array = arrayAfterRotation;
}

void ImageTile::flipArrayTopBottom() {
    int dimension = _array.size();
    for (int i = 0; i < dimension/2; i++) {
        std::iter_swap(_array.begin() + i, _array.begin() + dimension - 1 - i);
    }
}

void ImageTile::flipArrayLeftRight() {
    rotateArrayRight();
    flipArrayTopBottom();
    rotateArrayRight();
    rotateArrayRight();
    rotateArrayRight();
}

std::vector<std::string> & ImageTile::getArray() {
    return _array;
}

int ImageTile::getTileId() {
    return _tileId;
}
