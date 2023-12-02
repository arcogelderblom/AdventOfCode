#include <vector>
#include <string>

class BingoCard
{
private:
    std::vector< std::vector<int> > _card;
    std::vector< std::vector<bool> > _crossedElements;
    bool _isChangedSinceLastNum = false;
public:
    BingoCard(std::string card);
    void crossNumber(int num);
    bool hasBingo();
    int getSumUnmarkedNumbers();
    void printCard();
    friend bool operator==(const BingoCard& lhs, const BingoCard& rhs)
    {
        return lhs._card == rhs._card && lhs._crossedElements == rhs._crossedElements;
    }
};