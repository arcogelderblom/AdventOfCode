#include <iostream>
#include <chrono>
#include <tuple>
#include <set>
#include <map>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::tuple<int, int, int> Rotation;
typedef std::tuple<int, int, int> Coordinate;

std::vector< std::vector<std::string> > splitVectors(const std::vector<std::string> & src, const std::string & delimiter)
{
    std::vector< std::vector<std::string> > result;
    for (std::string item : src)
    {
        result.push_back(StringParser::toVector(item, delimiter));
    }
    return result;
}


std::vector<Rotation> possibleRotations = {
    std::make_tuple(0, 0, 0),
    std::make_tuple(0, 0, 90),
    std::make_tuple(0, 0, 180),
    std::make_tuple(0, 0, 270),
    std::make_tuple(0, 90, 0),
    std::make_tuple(0, 90, 90),
    std::make_tuple(0, 90, 180),
    std::make_tuple(0, 90, 270),
    std::make_tuple(0, 180, 0),
    std::make_tuple(0, 180, 90),
    std::make_tuple(0, 180, 180),
    std::make_tuple(0, 180, 270),
    std::make_tuple(0, 270, 0),
    std::make_tuple(0, 270, 90),
    std::make_tuple(0, 270, 180),
    std::make_tuple(0, 270, 270),
    std::make_tuple(90, 0, 0),
    std::make_tuple(90, 0, 90),
    std::make_tuple(90, 0, 180),
    std::make_tuple(90, 0, 270),
    std::make_tuple(90, 180, 0),
    std::make_tuple(90, 180, 90),
    std::make_tuple(90, 180, 180),
    std::make_tuple(90, 180, 270)
};

void changeRotation(std::vector<Coordinate>& scannerBeacons, int rotateX, int rotateY, int rotateZ)
{
//                 x   y   z
//                 1   2   3      
// rotate x 90     1   3   -2         
// rotate x 180    1   -2  -3        
// rotate x 270    1   -3  2         
// rotate y 90     -3  2   1         
// rotate y 180    -1  2   -3        
// rotate y 270    3   2   -1
// rotate z 90     2   -1  3         
// rotate z 180    -1  -2  3        
// rotate z 270    -2  1   3
    std::vector<Coordinate> result;
    for (Coordinate& scannerBeacon : scannerBeacons)
    {
        if (rotateX == 90)
        {
            int tmp = std::get<1>(scannerBeacon) * -1;
            std::get<1>(scannerBeacon) = std::get<2>(scannerBeacon);
            std::get<2>(scannerBeacon) = tmp;
        }
        else if (rotateX == 180)
        {

            std::get<1>(scannerBeacon) *= -1;
            std::get<2>(scannerBeacon) *= -1;
        }
        else if (rotateX == 270)
        {
            int tmp = std::get<1>(scannerBeacon);
            std::get<1>(scannerBeacon) = std::get<2>(scannerBeacon) * -1;
            std::get<2>(scannerBeacon) = tmp;
        }

        if (rotateY == 90)
        {
            int tmp = std::get<0>(scannerBeacon);
            std::get<0>(scannerBeacon) = std::get<2>(scannerBeacon) * -1;
            std::get<2>(scannerBeacon) = tmp;
        }
        else if (rotateY == 180)
        {
            std::get<0>(scannerBeacon) *= -1;
            std::get<2>(scannerBeacon) *= -1;
        }
        else if (rotateY == 270)
        {
            int tmp = std::get<0>(scannerBeacon) * -1;
            std::get<0>(scannerBeacon) = std::get<2>(scannerBeacon);
            std::get<2>(scannerBeacon) = tmp;
        }

        if (rotateZ == 90)
        {
            int tmp = std::get<0>(scannerBeacon) * -1;
            std::get<0>(scannerBeacon) = std::get<1>(scannerBeacon);
            std::get<1>(scannerBeacon) = tmp;
        }
        else if (rotateZ == 180)
        {
            std::get<0>(scannerBeacon) *= -1;
            std::get<1>(scannerBeacon) *= -1;
        }
        else if (rotateZ == 270)
        {
            int tmp = std::get<0>(scannerBeacon);
            std::get<0>(scannerBeacon) = std::get<1>(scannerBeacon) * -1;
            std::get<1>(scannerBeacon) = tmp;
        }
    }
}

std::map<Coordinate, Coordinate> findCommonBeacons(std::vector<Coordinate>& firstScannerBeacons, std::vector<Coordinate>& secondScannerBeacons)
{
    std::map<Coordinate, Coordinate> commonPairs;
    for (int i = 0; i < firstScannerBeacons.size(); i++)
    {
        for (int j = 1; j < firstScannerBeacons.size(); j++)
        {   
            if (firstScannerBeacons[i] == firstScannerBeacons[j])
            {
                continue;
            }
            for (int k = 0; k < secondScannerBeacons.size(); k++)
            {
                 for (int l = 1; l < secondScannerBeacons.size(); l++)
                 {
                     if (secondScannerBeacons[k] == secondScannerBeacons[l])
                     {
                         continue;
                     }
                    if (std::get<0>(firstScannerBeacons[i]) - std::get<0>(firstScannerBeacons[j]) == std::get<0>(secondScannerBeacons[k]) - std::get<0>(secondScannerBeacons[l]) &&
                        std::get<1>(firstScannerBeacons[i]) - std::get<1>(firstScannerBeacons[j]) == std::get<1>(secondScannerBeacons[k]) - std::get<1>(secondScannerBeacons[l]) &&
                        std::get<2>(firstScannerBeacons[i]) - std::get<2>(firstScannerBeacons[j]) == std::get<2>(secondScannerBeacons[k]) - std::get<2>(secondScannerBeacons[l]))
                    {
                        commonPairs[firstScannerBeacons[i]] = secondScannerBeacons[k];
                        commonPairs[firstScannerBeacons[j]] = secondScannerBeacons[l];
                    }   
                 }
            }
        }
    }
    return commonPairs;
}

int getAmountUniqueBeacons(std::vector<std::string> scanners, std::map<int, std::pair<Coordinate, Rotation>>& scannersAndRotation)
{
    std::vector< std::vector<std::string> > scannersAndBeacons = splitVectors(scanners, "\n");
    std::map<int, std::vector<Coordinate>> scannersAndBeaconsCoordinates;
    
    for (std::vector<std::string> scannerAndBeacon : scannersAndBeacons)
    {
        std::vector<Coordinate> currentBeacons;
        for (auto it = scannerAndBeacon.begin() + 1; it != scannerAndBeacon.end(); it++)
        {
            std::vector<int> beaconStringSplitted = StringParser::toIntVector(*it, ",");
            Coordinate beacon = std::make_tuple(beaconStringSplitted[0], beaconStringSplitted[1], beaconStringSplitted[2]);
            currentBeacons.push_back(beacon);
        }
        scannersAndBeaconsCoordinates[std::stoi(StringParser::toVector(scannerAndBeacon[0], " ")[2])] = currentBeacons;
    }

    scannersAndRotation[0] = std::make_pair(std::make_tuple(0,0,0), std::make_tuple(0,0,0));
    std::map<Coordinate, std::vector<Coordinate>> scannersCoordinatesAndBeaconsCoordinates;
    scannersCoordinatesAndBeaconsCoordinates[std::make_tuple(0,0,0)] = scannersAndBeaconsCoordinates[0];

    while(scannersAndRotation.size() < scanners.size())
    {
        for (std::pair<int, std::pair<Coordinate, Rotation>> scannerAndRotation : scannersAndRotation)
        {
            for (std::pair<int, std::vector<Coordinate>> scannerAndBeaconsCoordinates : scannersAndBeaconsCoordinates)
            {
                if (scannerAndBeaconsCoordinates.first == scannerAndRotation.first || scannersAndRotation.find(scannerAndBeaconsCoordinates.first) != scannersAndRotation.end())
                {
                    continue;
                }
                
                for (Rotation rotation : possibleRotations)
                {
                    std::vector<Coordinate> currentBeacons = scannerAndBeaconsCoordinates.second;
                    changeRotation(currentBeacons, std::get<0>(rotation), std::get<1>(rotation), std::get<2>(rotation));
                    std::map<Coordinate, Coordinate> commonBeacons = findCommonBeacons(scannersCoordinatesAndBeaconsCoordinates[scannerAndRotation.second.first], currentBeacons);
                    if (commonBeacons.size() >= 12)
                    {
                        Coordinate scannerPosition = std::make_tuple(std::get<0>((*commonBeacons.begin()).first) - std::get<0>((*commonBeacons.begin()).second) + std::get<0>(scannerAndRotation.second.first), 
                                                                    std::get<1>((*commonBeacons.begin()).first) - std::get<1>((*commonBeacons.begin()).second) + std::get<1>(scannerAndRotation.second.first), 
                                                                    std::get<2>((*commonBeacons.begin()).first) - std::get<2>((*commonBeacons.begin()).second) + std::get<2>(scannerAndRotation.second.first));
                        scannersAndRotation[scannerAndBeaconsCoordinates.first] = std::make_pair(scannerPosition, rotation);   
                        scannersCoordinatesAndBeaconsCoordinates[scannerPosition] = currentBeacons;
                        break;
                    }
                }
            }
        }
    }

    // find unique coordinates
    std::set<Coordinate> uniqueBeacons; // set only holds unique elements
    for (std::pair<int, std::pair<Coordinate, Rotation>> scannerAndRotation : scannersAndRotation)
    {
        std::vector<Coordinate> scanner = { scannerAndRotation.second.first };
        for (Coordinate beaconCoordinate : scannersCoordinatesAndBeaconsCoordinates[scannerAndRotation.second.first])
        {
            Coordinate beaconRelativeTo0 = std::make_tuple(std::get<0>(beaconCoordinate) + std::get<0>(scanner[0]), 
                                                           std::get<1>(beaconCoordinate) + std::get<1>(scanner[0]), 
                                                           std::get<2>(beaconCoordinate) + std::get<2>(scanner[0]));
            uniqueBeacons.insert(beaconRelativeTo0);
        }
    }
    
    return uniqueBeacons.size();
}

int getLargestManhattanDistance(std::map<int, std::pair<Coordinate, Rotation>> scanners)
{
    int largestManhattanDistance = 0;
    for (std::pair<int, std::pair<Coordinate, Rotation>> scanner1 : scanners)
    {
        for (std::pair<int, std::pair<Coordinate, Rotation>> scanner2 : scanners)
        {
            int distance = std::abs(std::get<0>(scanner1.second.first) - std::get<0>(scanner2.second.first)) + 
                           std::abs(std::get<1>(scanner1.second.first) - std::get<1>(scanner2.second.first)) + 
                           std::abs(std::get<2>(scanner1.second.first) - std::get<2>(scanner2.second.first));
            if (distance > largestManhattanDistance)
            {
                largestManhattanDistance = distance;
            }
        }
    }
    return largestManhattanDistance;
}

int main(void)
{
    std::vector<std::string> testInput = StringParser::toVector("--- scanner 0 ---\n404,-588,-901\n528,-643,409\n-838,591,734\n390,-675,-793\n-537,-823,-458\n-485,-357,347\n-345,-311,381\n-661,-816,-575\n-876,649,763\n-618,-824,-621\n553,345,-567\n474,580,667\n-447,-329,318\n-584,868,-557\n544,-627,-890\n564,392,-477\n455,729,728\n-892,524,684\n-689,845,-530\n423,-701,434\n7,-33,-71\n630,319,-379\n443,580,662\n-789,900,-551\n459,-707,401\n\n--- scanner 1 ---\n686,422,578\n605,423,415\n515,917,-361\n-336,658,858\n95,138,22\n-476,619,847\n-340,-569,-846\n567,-361,727\n-460,603,-452\n669,-402,600\n729,430,532\n-500,-761,534\n-322,571,750\n-466,-666,-811\n-429,-592,574\n-355,545,-477\n703,-491,-529\n-328,-685,520\n413,935,-424\n-391,539,-444\n586,-435,557\n-364,-763,-893\n807,-499,-711\n755,-354,-619\n553,889,-390\n\n--- scanner 2 ---\n649,640,665\n682,-795,504\n-784,533,-524\n-644,584,-595\n-588,-843,648\n-30,6,44\n-674,560,763\n500,723,-460\n609,671,-379\n-555,-800,653\n-675,-892,-343\n697,-426,-610\n578,704,681\n493,664,-388\n-671,-858,530\n-667,343,800\n571,-461,-707\n-138,-166,112\n-889,563,-600\n646,-828,498\n640,759,510\n-630,509,768\n-681,-892,-333\n673,-379,-804\n-742,-814,-386\n577,-820,562\n\n--- scanner 3 ---\n-589,542,597\n605,-692,669\n-500,565,-823\n-660,373,557\n-458,-679,-417\n-488,449,543\n-626,468,-788\n338,-750,-386\n528,-832,-391\n562,-778,733\n-938,-730,414\n543,643,-506\n-524,371,-870\n407,773,750\n-104,29,83\n378,-903,-323\n-778,-728,485\n426,699,580\n-438,-605,-362\n-469,-447,-387\n509,732,623\n647,635,-688\n-868,-804,481\n614,-800,639\n595,780,-596\n\n--- scanner 4 ---\n727,592,562\n-293,-554,779\n441,611,-461\n-714,465,-776\n-743,427,-804\n-660,-479,-426\n832,-632,460\n927,-485,-438\n408,393,-506\n466,436,-512\n110,16,151\n-258,-428,682\n-393,719,612\n-211,-452,876\n808,-476,-593\n-575,615,604\n-485,667,467\n-680,325,-822\n-627,-443,-432\n872,-547,-609\n833,512,582\n807,604,487\n839,-516,451\n891,-625,532\n-652,-548,-490\n30,-46,-14", "\n\n");
    std::map<int, std::pair<Coordinate, Rotation>> testScannersAndRotation;
    assert(getAmountUniqueBeacons(testInput, testScannersAndRotation) == 79);

    FileHandler fileHandler("input-files/2021/day19.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::map<int, std::pair<Coordinate, Rotation>> scannersAndRotation;
    std::cout << "Day 19, puzzle 1: " << std::flush << getAmountUniqueBeacons(input, scannersAndRotation) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getLargestManhattanDistance(testScannersAndRotation) == 3621);    
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 19, puzzle 2: " << std::flush << getLargestManhattanDistance(scannersAndRotation) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
