#include <vector>
#include <string>

class Submarine
{
private:
    int _depth = 0;
    int _horizontalPosition = 0;
    int _aim = 0;
public:
    void travel(std::vector<std::string> commands, bool useAim = false);
    int getHorizontalPosition();
    int getDepth();
};