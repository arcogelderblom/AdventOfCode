#include <string>
#include <vector>

class InputFile 
{
private:
    std::string _fileContentBuffer;
    std::vector<std::string> getContentUsingDelimiter(std::string delimiter);
public:
    InputFile(std::string path);
    std::vector<int> getContentAsInt(std::string delimiter);
    std::vector<std::string> getContentAsString(std::string delimiter);
};