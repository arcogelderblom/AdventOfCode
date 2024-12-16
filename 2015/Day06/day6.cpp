#include <iostream>

#include "StringParser.hpp"
#include "FileHandler.hpp"

enum Instruction
{
    TURN_OFF,
    TURN_ON,
    TOGGLE
};

int executeInstructionsAndGetTotalLightsOn(std::vector<std::string> instructions)
{
    std::vector<std::vector<bool>> grid (1000, std::vector<bool>(1000, false));

    for (std::string instruction : instructions)
    {
        Instruction current_instruction;
        if (instruction.find("turn off") != std::string::npos)
        {
            current_instruction = TURN_OFF;
        }
        else if (instruction.find("turn on") != std::string::npos)
        {
            current_instruction = TURN_ON;
        }
        else if (instruction.find("toggle") != std::string::npos)
        {
            current_instruction = TOGGLE;
        }
        
        std::string start_point_str = instruction.substr(instruction.find_first_of("0123456789"), instruction.find(" through") - instruction.size());
        std::string end_point_str = instruction.substr(instruction.find_last_of(' ') + 1);
        int start_x = std::stoi(start_point_str.substr(0, start_point_str.find_first_of(',')));
        int start_y = std::stoi(start_point_str.substr(start_point_str.find_first_of(',') + 1));
        int end_x = std::stoi(end_point_str.substr(0, end_point_str.find_first_of(',')));
        int end_y = std::stoi(end_point_str.substr(end_point_str.find_first_of(',') + 1));

        for (int y = start_y; y <= end_y; y++)
        {
            for (int x = start_x; x <= end_x; x++)
            {
                switch(current_instruction)
                {
                    case (TURN_OFF):
                    {
                        grid[y][x] = false;
                        break;
                    }
                    case (TURN_ON):
                    {
                        grid[y][x] = true;
                        break;
                    }
                    case (TOGGLE):
                    {
                        grid[y][x] = !grid[y][x];
                        break;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid.size(); x++)
        {
            if (grid[y][x])
            {
                result++;
            }
        }
    }
    return result;
}

long long executeInstructionsAndGetTotalBrightness(std::vector<std::string> instructions)
{
    std::vector<std::vector<int>> grid (1000, std::vector<int>(1000, 0));

    for (std::string instruction : instructions)
    {
        Instruction current_instruction;
        if (instruction.find("turn off") != std::string::npos)
        {
            current_instruction = TURN_OFF;
        }
        else if (instruction.find("turn on") != std::string::npos)
        {
            current_instruction = TURN_ON;
        }
        else if (instruction.find("toggle") != std::string::npos)
        {
            current_instruction = TOGGLE;
        }
        
        std::string start_point_str = instruction.substr(instruction.find_first_of("0123456789"), instruction.find(" through") - instruction.size());
        std::string end_point_str = instruction.substr(instruction.find_last_of(' ') + 1);
        int start_x = std::stoi(start_point_str.substr(0, start_point_str.find_first_of(',')));
        int start_y = std::stoi(start_point_str.substr(start_point_str.find_first_of(',') + 1));
        int end_x = std::stoi(end_point_str.substr(0, end_point_str.find_first_of(',')));
        int end_y = std::stoi(end_point_str.substr(end_point_str.find_first_of(',') + 1));

        for (int y = start_y; y <= end_y; y++)
        {
            for (int x = start_x; x <= end_x; x++)
            {
                switch(current_instruction)
                {
                    case (TURN_OFF):
                    {
                        if (grid[y][x] > 0)
                        {
                            grid[y][x]--;
                        }
                        break;
                    }
                    case (TURN_ON):
                    {
                        grid[y][x]++;
                        break;
                    }
                    case (TOGGLE):
                    {
                        grid[y][x] += 2;
                        break;
                    }
                }
            }
        }
    }

    long long brightness = 0;
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid.size(); x++)
        {
            brightness+=grid[y][x];
        }
    }
    return brightness;
}

int main(void) 
{
    FileHandler FileHandler("input-files/2015/day06.txt");
    std::vector<std::string> input = StringParser::toVector(FileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();

    std::cout << "Day 6, puzzle 1: " << std::flush << executeInstructionsAndGetTotalLightsOn(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 2: " << std::flush << executeInstructionsAndGetTotalBrightness(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}