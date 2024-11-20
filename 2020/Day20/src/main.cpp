#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "ImageAssembler.hpp"
#include "ImageTile.hpp"
#include "ImageProcessor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day20.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");

    ImageAssembler assembler(input);
    assembler.assemble();
    std::vector<ImageTile> cornerTiles = assembler.getCornerTileIds();
    long long result = 1;
    for (ImageTile tile : cornerTiles) {
        result *= tile.getTileId();
    }
    std::cout << "Puzzle one output: " << result << std::endl;

    ImageProcessor processor(assembler.getImage());
    std::cout << "Puzzle two output: " << processor.getRoughWaters() << std::endl;
}
