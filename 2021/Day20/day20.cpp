#include <iostream>
#include <chrono>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

char getPixelAtLocation(int y, int x, std::vector<std::string> image, char returnOutofBounds)
{
    if (y < 0 || y >= image.size() || x < 0 || x >= image[0].size())
    {
        return returnOutofBounds;
    }
    return image[y][x];
}

int algorithmIndexNumForPosition(int x, int y, std::vector<std::string> image, std::string algorithm, int currentIteration)
{
	std::string toConvertToBinary;
    char returnOutofBounds = '.';
    if (currentIteration % 2 != 0 && algorithm[0] == '#')
    {
        returnOutofBounds = '#';
    }
    
	toConvertToBinary += getPixelAtLocation(y-1, x-1, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y-1, x, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y-1, x+1, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y, x-1, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y, x, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y, x+1, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y+1, x-1, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y+1, x, image, returnOutofBounds);
	toConvertToBinary += getPixelAtLocation(y+1, x+1, image, returnOutofBounds);
	std::string binaryString;
    
	for (char c : toConvertToBinary)
	{
		binaryString += c == '#' ? "1" : "0";
	}
    
	return std::stoi(binaryString, 0, 2);
}

std::vector<std::string> enhanceImage(std::vector<std::string> image, std::string algorithm, int currentIteration)
{
	std::vector<std::string> result;
    
    for (int y = -1; y <= (int)image.size(); y++)
	{
		std::string currentImageRow;
		for (int x = -1; x <= (int)image[0].size(); x++)
		{
			currentImageRow += algorithm[algorithmIndexNumForPosition(x, y, image, algorithm, currentIteration)];
		}
		result.push_back(currentImageRow);
	}
	
	return result;
}

long long getLitPixelsAfterEnhancing(std::vector<std::string> image, std::string algorithm, int amountOfTimes)
{
	for (int i = 0; i < amountOfTimes; i++)
	{
		image = enhanceImage(image, algorithm, i);
 	}
	long result = 0;
	for (std::string imageRow : image)
	{
		result += std::count(imageRow.begin(), imageRow.end(), '#');
	}
    
	return result;
}

int main(void)
{
    std::vector<std::string> testInput = StringParser::toVector("..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#\n\n#..#.\n#....\n##..#\n..#..\n..###", "\n\n");
	std::string testImageEnhancementAlgorithm = testInput[0];
	std::vector<std::string> testImage = StringParser::toVector(testInput[1], "\n");
    assert(getLitPixelsAfterEnhancing(testImage, testImageEnhancementAlgorithm, 2) == 35);
    
    FileHandler fileHandler("input-files/2021/day20.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
	std::string imageEnhancementAlgorithm = input[0];
	std::vector<std::string> image = StringParser::toVector(input[1], "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 1: " << getLitPixelsAfterEnhancing(image, imageEnhancementAlgorithm, 2) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getLitPixelsAfterEnhancing(testImage, testImageEnhancementAlgorithm, 50) == 3351);   
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 20, puzzle 2: ";
    std::cout << getLitPixelsAfterEnhancing(image, imageEnhancementAlgorithm, 50) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}