#include <vector>
#include <string>

class StringOperations
{
public:
    static std::vector<std::string> splitString(std::string stringToSplit, std::string delimiter);
    static std::vector<int> splitStringIntoSeparateNum(std::string stringToSplit);
};