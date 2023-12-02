#include "bingocard.hpp"
#include <vector>
#include <string>

class Bingo
{
private:
    std::vector<BingoCard> _bingoCards;
public:
    Bingo(std::vector<std::string> bingoCards);
    int play(std::vector<int> drawnNumbers, bool playUntilLastOneWins = false);
};