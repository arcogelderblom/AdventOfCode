#include "submarine.hpp"

void Submarine::travel(std::vector<std::string> commands, bool useAim)
{
    for (std::string command : commands) 
    {
        std::string direction = command.substr(0, command.find(' '));
        int units = std::stoi(command.substr(command.find(' ') + 1));  
        if (direction == "forward")
        {
            if (useAim) 
            {
                _horizontalPosition += units;
                _depth += _aim * units;
            }
            else 
            {
                _horizontalPosition += units;
            }
        }
        else if (direction == "down")
        {
            if (useAim) 
            {
                _aim += units;
            }
            else 
            {
                _depth += units;
            }
        }
        else if (direction == "up") 
        {
            if (useAim) 
            {
                _aim -= units;
            }
            else 
            {
               _depth -= units;
            }
        }
    }
}

int Submarine::getHorizontalPosition()
{
    return _horizontalPosition;
}

int Submarine::getDepth()
{
    return _depth;
}
