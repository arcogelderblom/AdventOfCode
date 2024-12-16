#include <vector>
#include <string>

class VectorOperations
{
public:
    static std::vector< std::vector<std::string> > splitVectorInSubVectors(std::vector<std::string> vector, std::string delimiter);
    static std::vector<int> stringVectorToIntVector(std::vector<std::string> stringVector);
    static std::vector< std::vector<int> > stringVectorToSeparatedIntVector(std::vector<std::string> stringVector);
};