#include <iostream>
#include <map>
#include <chrono>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

int count1478DigitsInOutputValue(std::vector<std::string> notesAndOutput)
{
    int result = 0;
    for (std::string item : notesAndOutput)
    {
        std::vector<std::string> notesAndOutputVector = StringParser::toVector(item, " | ");
        std::vector<std::string> notes = StringParser::toVector(notesAndOutputVector[0], " ");
        std::vector<std::string> output = StringParser::toVector(notesAndOutputVector[1], " ");
        std::string representation1, representation4, representation7, representation8;
        for (std::string note : notes)
        {
            if (note.size() == 2) // 1
            {
                representation1 = note;
            }
            else if (note.size() == 4) // 4
            {
                representation4 = note;
            }
            else if (note.size() == 3) // 7
            {
                representation7 = note;
            }
            else if (note.size() == 7) // 8
            {
                representation8 = note;
            }
        }
        

        result += std::count_if(output.begin(), output.end(), [&](const std::string x){ return x.find_first_not_of(representation1) == std::string::npos && x.size() == representation1.size(); });
        result += std::count_if(output.begin(), output.end(), [&](const std::string x){ return x.find_first_not_of(representation4) == std::string::npos && x.size() == representation4.size(); });
        result += std::count_if(output.begin(), output.end(), [&](const std::string x){ return x.find_first_not_of(representation7) == std::string::npos && x.size() == representation7.size(); });
        result += std::count_if(output.begin(), output.end(), [&](const std::string x){ return x.find_first_not_of(representation8) == std::string::npos && x.size() == representation8.size(); });
    }
    return result;
}

int decodeOutput(std::string notesAndOutput)
{
    std::string decodedOutput;
    std::map<std::string, std::string> translation;
    std::vector<std::string> notesAndOutputVector = StringParser::toVector(notesAndOutput, " | ");
    std::vector<std::string> notes = StringParser::toVector(notesAndOutputVector[0], " ");
    std::vector<std::string> output = StringParser::toVector(notesAndOutputVector[1], " ");
    std::string representation1 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 2; });
    std::string representation4 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 4; });
    std::string representation7 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 3; });
    std::string representation8 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 7; });
    std::string representation9 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 6 && representation4.find_first_not_of(note) == std::string::npos; });
    std::string representation0 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 6 && representation7.find_first_not_of(note) == std::string::npos &&  representation4.find_first_not_of(note) != std::string::npos; });
    std::string representation3 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 5 && representation7.find_first_not_of(note) == std::string::npos; });
    std::string representation6 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 6 && representation7.find_first_not_of(note) != std::string::npos && note.find_first_not_of(representation4) != std::string::npos; });
    
    char rightTopSegment = representation4[representation4.find_first_not_of(representation6)];
    std::string representation2 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 5 && representation7.find_first_not_of(note) != std::string::npos && note.find(rightTopSegment) != std::string::npos; });
    std::string representation5 = *std::find_if(notes.begin(), notes.end(), [&](const std::string note) { return note.size() == 5 && representation7.find_first_not_of(note) != std::string::npos && note.find(rightTopSegment) == std::string::npos; });
    
    std::vector<std::string> representation = { representation0, representation1, representation2, representation3, representation4, representation5, representation6, representation7, representation8, representation9 };

    for (auto item : output)
    {
        decodedOutput += std::to_string(std::distance(representation.begin(), std::find_if(representation.begin(), representation.end(), [&](const std::string representationItem){ return item.size() == representationItem.size() && item.find_first_not_of(representationItem) == std::string::npos; })));
    }
    
    return std::stoi(decodedOutput);
}

unsigned long getOutputSum(std::vector<std::string> notesAndOutput)
{
    unsigned long sum = 0;
    for (auto item : notesAndOutput)
    {
        sum += decodeOutput(item);
    }
    
    return sum;
}

int main(void)
{
    std::vector<std::string> testInput = {"be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe", "edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc", "fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg", "fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb", "aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea", "fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb", "dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe", "bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef", "egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb", "gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce"};
    assert(count1478DigitsInOutputValue(testInput) == 26);
    
    FileHandler fileHandler("input-files/2021/day08.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 1: " << std::flush << count1478DigitsInOutputValue(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getOutputSum(testInput) == 61229);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 2: " << std::flush << getOutputSum(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
