#include <string>
#include <vector>
#include <set>
#include <tuple>

class Cube
{
public:
    bool on;
    long long xMin;
    long long xMax;
    long long yMin;
    long long yMax;
    long long zMin;
    long long zMax;

    Cube();
    Cube(long long xMin, long long xMax, long long yMin, long long yMax, long long zMin, long long zMax, bool on);
    Cube(std::string bounds, bool on);
    bool intersects(Cube cube);
    bool contains(Cube cube);
    std::vector<Cube> split(Cube cube);
    bool join(Cube cube);
    std::set<std::tuple<long long,long long,long long>> getAllCoordinates();
    long long getAmountOfCoordinatesContained(bool puzzle1 = false);

    bool operator==(const Cube& other) const
    {
        return xMin == other.xMin && xMax == other.xMax &&  yMin == other.yMin && yMax == other.yMax && zMin == other.zMin && zMax == other.zMax && on == other.on;
    }
};