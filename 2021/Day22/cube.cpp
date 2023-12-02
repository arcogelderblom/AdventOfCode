#include "cube.hpp"

#include <iostream>

#include "StringParser.hpp"

Cube::Cube():
    on(false),
    xMin(0),
    xMax(0),
    yMin(0),
    yMax(0),
    zMin(0),
    zMax(0)
{}

Cube::Cube(long long xMin, long long xMax, long long yMin, long long yMax, long long zMin, long long zMax, bool on):
    on(on),
    xMin(xMin),
    xMax(xMax),
    yMin(yMin),
    yMax(yMax),
    zMin(zMin),
    zMax(zMax)
{}

Cube::Cube(std::string bounds, bool on):
    on(on)
{
    std::string xStartAndEnd = StringParser::toVector(bounds, ",")[0].substr(2);
    std::string yStartAndEnd = StringParser::toVector(bounds, ",")[1].substr(2);
    std::string zStartAndEnd = StringParser::toVector(bounds, ",")[2].substr(2);
    xMin = std::stoi(StringParser::toVector(xStartAndEnd, "..")[0]);
    xMax = std::stoi(StringParser::toVector(xStartAndEnd, "..")[1]);
    yMin = std::stoi(StringParser::toVector(yStartAndEnd, "..")[0]);
    yMax = std::stoi(StringParser::toVector(yStartAndEnd, "..")[1]);
    zMin = std::stoi(StringParser::toVector(zStartAndEnd, "..")[0]);
    zMax = std::stoi(StringParser::toVector(zStartAndEnd, "..")[1]);
}

bool Cube::intersects(Cube cube)
{
    if (xMax < cube.xMin || cube.xMax < xMin)
    {
        return false;
    }
    if (yMax < cube.yMin || cube.yMax < yMin)
    {
        return false;
    }
    if (zMax < cube.zMin || cube.zMax < zMin)
    {
        return false;
    }
    return true;
}

std::vector<Cube> Cube::split(Cube cube)
{
    std::vector<Cube> splittedCubes;
    Cube intersectCubeToRemove;
    intersectCubeToRemove.xMin = std::max(xMin, cube.xMin);
    intersectCubeToRemove.yMin = std::max(yMin, cube.yMin);
    intersectCubeToRemove.zMin = std::max(zMin, cube.zMin);
    intersectCubeToRemove.xMax = std::min(xMax, cube.xMax);
    intersectCubeToRemove.yMax = std::min(yMax, cube.yMax);
    intersectCubeToRemove.zMax = std::min(zMax, cube.zMax);
    
    if (xMin < intersectCubeToRemove.xMin)
    {
        Cube newCube(xMin, intersectCubeToRemove.xMin - 1, yMin, yMax, intersectCubeToRemove.zMin, intersectCubeToRemove.zMax, true);
        splittedCubes.push_back(newCube);
    }
    if (intersectCubeToRemove.xMax < xMax)
    {
        Cube newCube(intersectCubeToRemove.xMax + 1, xMax, yMin, yMax, intersectCubeToRemove.zMin, intersectCubeToRemove.zMax, true);
        splittedCubes.push_back(newCube);
    }
    if (yMin < intersectCubeToRemove.yMin)
    {
        Cube newCube(intersectCubeToRemove.xMin, intersectCubeToRemove.xMax, yMin, intersectCubeToRemove.yMin -1, intersectCubeToRemove.zMin, intersectCubeToRemove.zMax, true);
        splittedCubes.push_back(newCube);
    }
    if (intersectCubeToRemove.yMax < yMax)
    {
        Cube newCube(intersectCubeToRemove.xMin, intersectCubeToRemove.xMax, intersectCubeToRemove.yMax + 1, yMax, intersectCubeToRemove.zMin, intersectCubeToRemove.zMax, true);
        splittedCubes.push_back(newCube);
    }
    if (zMin < intersectCubeToRemove.zMin)
    {
        Cube newCube(xMin, xMax, yMin, yMax, zMin, intersectCubeToRemove.zMin - 1, true);
        splittedCubes.push_back(newCube);
    }
    if (intersectCubeToRemove.zMax < zMax)
    {
        Cube newCube(xMin, xMax, yMin, yMax, intersectCubeToRemove.zMax + 1, zMax, true);
        splittedCubes.push_back(newCube);
    }

    return splittedCubes;
}

bool Cube::join(Cube cube)
{
    // join cubes that form 1 together
    bool sameX = (xMin == cube.xMin && xMax == cube.xMax);
    bool sameY = (yMin == cube.yMin && yMax == cube.yMax);
    bool sameZ = (zMin == cube.zMin && zMax == cube.zMax);
    
    bool joined = false;
    if (sameX && sameY)
    {
        if (zMax == cube.zMin - 1)
        {
            zMax = cube.zMax;
            joined = true;
        }
        else if (cube.zMax + 1 == zMin)
        {
            zMin = cube.zMin;
            joined = true;
        }
    }
    else if (sameX && sameZ)
    {
        if (yMax == cube.yMin - 1)
        {
            yMax = cube.yMax;
            joined = true;
        }
        else if (cube.yMax + 1 == yMin)
        {
            yMin = cube.yMin;
            joined = true;
        }
    }
    else if (sameY && sameZ)
    {
        if (xMax == cube.xMin - 1)
        {
            xMax = cube.xMax;
            joined = true;
        }
        else if (cube.xMax + 1 == yMin)
        {
            xMin = cube.xMin;
            joined = true;
        }
    }
    return joined;
}

std::set<std::tuple<long long,long long,long long>> Cube::getAllCoordinates()
{
    std::set<std::tuple<long long,long long,long long>> result;
    for (long long x = xMin; x <= xMax; x++)
    {
        for (long long y = yMin; y <= yMax; y++)
        {
            for (long long z = zMin; z <= zMax; z++)
            {
                result.insert(std::make_tuple(x,y,z));
            }
        }
    }
    return result;
}

long long Cube::getAmountOfCoordinatesContained(bool puzzle1)
{
    if (puzzle1)
    {
        if ((xMax < -50 || xMin > 50) || (yMax < -50 || yMin > 50) || (zMax < -50 || zMin > 50))
        {
            return 0;
        }
        
        return (std::min(xMax, (long long)50) - std::max(xMin, (long long)-50) + 1) * (std::min(yMax, (long long)50) - std::max(yMin, (long long)-50) + 1) * (std::min(zMax, (long long)50) - std::max(zMin, (long long)-50) + 1);
    }
    return (xMax - xMin + 1) * (yMax - yMin + 1) * (zMax - zMin + 1);
}
