#include <map>
#include <string>

class ALU
{
    int _currentInputIndex = 0;
    std::string _input;
public:
    ALU(std::string input);
    void executeInstruction(std::string instruction, std::map<std::string, int>& variableAndValues);
};