#include <iostream>
#include <cassert>
#include <chrono>

#include <string>
#include <iterator>
#include <utility>
#include <set>
#include <list>
#include <map>

#include "FileHandler.hpp"
#include "StringParser.hpp"

typedef std::pair<int, int> Coordinate;

enum Direction
{
    DOWN,
    LEFT,
    UP,
    RIGHT
};

struct Node
{
    Coordinate c;
    Direction d;
    int h;
    int g;
    int stepsInDirection = 1;
    Node(Coordinate c, Direction d, int h, int g) :
        c(c),
        d(d),
        h(h),
        g(g)
    {}
    bool operator<(const Node& rhs) const
    {
        return (h + g) < (rhs.h + rhs.g);
    }
    bool operator>(const Node& rhs) const
    {
        return (h + g) > (rhs.h + rhs.g);
    }
    bool operator==(const Node& rhs) const
    {
        return c == rhs.c && d == rhs.d && stepsInDirection == rhs.stepsInDirection;
    }
};

bool isInBounds(const std::vector<std::string> & input, const Coordinate & coordinate)
{
    return (coordinate.first >= 0 && coordinate.first < input[0].size() && coordinate.second >= 0 && coordinate.second < input.size());
}

int getHeuristic(const Coordinate & a, const Coordinate & b)
{
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
   
}

Coordinate getNewCoordinate(const Coordinate & current, const Direction & direction)
{
    switch (direction)
    {
        case (Direction::DOWN) :
        {
            return Coordinate(current.first, current.second + 1);
        }
        case (Direction::LEFT) :
        {
            return Coordinate(current.first - 1, current.second);
        }
        case (Direction::UP) :
        {
            return Coordinate(current.first, current.second - 1);
        }
        case (Direction::RIGHT) :
        {
            return Coordinate(current.first + 1, current.second);
        }
    }
    return Coordinate(-1, -1);
}

Coordinate getNewUltraCrucibleCoordinate(const Coordinate & current, const Direction & direction)
{
    switch (direction)
    {
        case (Direction::DOWN) :
        {
            return Coordinate(current.first, current.second + 4);
        }
        case (Direction::LEFT) :
        {
            return Coordinate(current.first - 4, current.second);
        }
        case (Direction::UP) :
        {
            return Coordinate(current.first, current.second - 4);
        }
        case (Direction::RIGHT) :
        {
            return Coordinate(current.first + 4, current.second);
        }
    }
    return Coordinate(-1, -1);
}

std::vector<Node> getSuccessors(const std::vector<std::string> & input, const Node & current, const Coordinate & end)
{
    std::vector<Node> result;
    switch (current.d)
    {
        case (Direction::DOWN) :
        case (Direction::UP) :
        {
            Coordinate left = getNewCoordinate(current.c, Direction::LEFT);
            if (isInBounds(input, left))
            {
                Node newLeftNode(left, Direction::LEFT, getHeuristic(left, end), current.g + (input[left.second][left.first] - '0'));
                result.push_back(newLeftNode);
            }
            Coordinate right = getNewCoordinate(current.c, Direction::RIGHT);
            if (isInBounds(input, right))
            {
                Node newRightNode(right, Direction::RIGHT, getHeuristic(right, end), current.g + (input[right.second][right.first] - '0'));
                result.push_back(newRightNode);
            }
            break;
        }
        case (Direction::LEFT) :
        case (Direction::RIGHT) :
        {
            Coordinate up = getNewCoordinate(current.c, Direction::UP);
            if (isInBounds(input, up))
            {
                Node newUpNode(up, Direction::UP, getHeuristic(up, end), current.g + (input[up.second][up.first] - '0'));
                result.push_back(newUpNode);
            }
            Coordinate down = getNewCoordinate(current.c, Direction::DOWN);
            if (isInBounds(input, down))
            {
                Node newDownNode(down, Direction::DOWN, getHeuristic(down, end), current.g + (input[down.second][down.first] - '0'));
                result.push_back(newDownNode);
            }
            break;
        }
    }

    if (current.stepsInDirection < 3)
    {
        // also generate in current direction
        Coordinate continued = getNewCoordinate(current.c, current.d);
        if (isInBounds(input, continued))
        {
            Node newContinuedNode(continued, current.d, getHeuristic(continued, end), current.g + (input[continued.second][continued.first] - '0'));
            newContinuedNode.stepsInDirection = current.stepsInDirection + 1;
            result.push_back(newContinuedNode);
        }
    }
    return result;
}

std::vector<Node> getUltraCrucibleSuccessors(const std::vector<std::string> & input, const Node & current, const Coordinate & end)
{
    std::vector<Node> result;
    switch (current.d)
    {
        case (Direction::DOWN) :
        case (Direction::UP) :
        {
            Coordinate left = getNewUltraCrucibleCoordinate(current.c, Direction::LEFT);
            if (isInBounds(input, left))
            {
                // add skipped values
                int skippedG = 0;
                for (int i = 1; i < 4; i++) { skippedG += input[left.second][left.first + i] - '0'; }
                Node newLeftNode(left, Direction::LEFT, getHeuristic(left, end), current.g + (input[left.second][left.first] - '0') + skippedG);
                newLeftNode.stepsInDirection = 4;
                result.push_back(newLeftNode);
            }
            Coordinate right = getNewUltraCrucibleCoordinate(current.c, Direction::RIGHT);
            if (isInBounds(input, right))
            {
                // add skipped values
                int skippedG = 0;
                for (int i = 1; i < 4; i++) { skippedG += input[right.second][right.first - i] - '0'; }
                Node newRightNode(right, Direction::RIGHT, getHeuristic(right, end), current.g + (input[right.second][right.first] - '0') + skippedG);
                newRightNode.stepsInDirection = 4;
                result.push_back(newRightNode);
            }
            break;
        }
        case (Direction::LEFT) :
        case (Direction::RIGHT) :
        {
            Coordinate up = getNewUltraCrucibleCoordinate(current.c, Direction::UP);
            if (isInBounds(input, up))
            {
                // add skipped values
                int skippedG = 0;
                for (int i = 1; i < 4; i++) { skippedG += input[up.second + i][up.first] - '0'; }
                Node newUpNode(up, Direction::UP, getHeuristic(up, end), current.g + (input[up.second][up.first] - '0') + skippedG);
                newUpNode.stepsInDirection = 4;
                result.push_back(newUpNode);
            }
            Coordinate down = getNewUltraCrucibleCoordinate(current.c, Direction::DOWN);
            if (isInBounds(input, down))
            {
                // add skipped values
                int skippedG = 0;
                for (int i = 1; i < 4; i++) { skippedG += input[down.second - i][down.first] - '0'; }
                Node newDownNode(down, Direction::DOWN, getHeuristic(down, end), current.g + (input[down.second][down.first] - '0') + skippedG);
                newDownNode.stepsInDirection = 4;
                result.push_back(newDownNode);
            }
            break;
        }
    }

    if (current.stepsInDirection < 10)
    {
        // also generate in current direction
        Coordinate continued = getNewCoordinate(current.c, current.d);
        if (isInBounds(input, continued))
        {
            Node newContinuedNode(continued, current.d, getHeuristic(continued, end), current.g + (input[continued.second][continued.first] - '0'));
            newContinuedNode.stepsInDirection = current.stepsInDirection + 1;
            result.push_back(newContinuedNode);
        }
    }
    return result;
}

void outputNode(const Node & current)
{
    std::cout << "c: " << current.c.first << "," << current.c.second /*<<" " << current.d*/ << "\tg: " << current.g << "\th: " <<current.h << "\tf: " << current.g + current.h << std::endl;
}

int getLeastHeatLoss(const std::vector<std::string> & input, const Coordinate & start, const Direction & startDirection, const Coordinate & end, bool part2 = false)
{
    Node startNode(Node(start, startDirection, 0, 0));
    startNode.stepsInDirection = 0;
    std::vector<Node> open { startNode };
    std::map<Coordinate, std::vector<Node>> closed; // because of different paths we can have multiple closed per coordinate
    while (!open.empty())
    {
        // sort based on 'f()' from low-high since we want the Node with lowest 'f()'
        std::sort(open.begin(), open.end(), [&](const Node & n1, const Node & n2){ return n1 > n2; });
        // take the last element since that has the lowest 'f()'
        Node n(open.back());
        open.pop_back();
        
        if (n.c == end)
        {
            return n.g;
        }


        std::vector<Node> successors = part2 ? getUltraCrucibleSuccessors(input, n, end) : getSuccessors(input, n, end);
        for (const Node & successor : successors)
        {
            auto itOpen = std::find(open.begin(), open.end(), successor);
            if (itOpen == open.end())
            {
                auto itClosed = std::find(closed[successor.c].begin(), closed[successor.c].end(), successor);
                if (itClosed == closed[successor.c].end() || successor.g < (*itClosed).g)
                {
                    open.emplace_back(successor);   
                }
            }
        }

        closed[n.c].push_back(n);
    }
    
    return 0;
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    result = getLeastHeatLoss(input, Coordinate(0, 0), Direction::DOWN, Coordinate(input[0].size() - 1, input.size() - 1));
    return result;
}

int part2(const std::vector<std::string> & input) 
{
    int result = 0;
    result = getLeastHeatLoss(input, Coordinate(0, 0), Direction::DOWN, Coordinate(input[0].size() - 1, input.size() - 1), true);
    return result;
}

int main(void) 
{
    FileHandler fileHandlerTest("input-files/2023/day17_testinput.txt");
    std::vector<std::string> testInput = StringParser::toVector(fileHandlerTest.getBuffer(), "\n");
    assert(part1(testInput) == 102);

    FileHandler fileHandler("input-files/2023/day17.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");

    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    assert(part2(testInput) == 94);

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}