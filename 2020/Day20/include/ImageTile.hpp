#pragma once

#include <vector>
#include <string>

class ImageTile {
private:
    int _tileId;
    std::vector<std::string> _array;
public:
    ImageTile();
    ImageTile(std::string idAndArray);
    void rotateArrayRight();
    void flipArrayTopBottom();
    void flipArrayLeftRight();
    std::vector<std::string> & getArray();
    int getTileId();

    friend bool operator<(const ImageTile& l, const ImageTile& r) {
        return l._tileId < r._tileId;
    }
};