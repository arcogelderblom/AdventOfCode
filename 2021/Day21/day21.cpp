#include <iostream>
#include <chrono>
#include <map>
#include <set>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

struct Player
{
	int playerNum;
	int score = 0;
    int currentPos;
    friend bool operator<(const Player& lhs, const Player& rhs)
    {
        return lhs.playerNum < rhs.playerNum && lhs.score < rhs.score && lhs.currentPos < rhs.currentPos;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& p)
    {
        os << "Player " << p.playerNum << " | Current position: " << p.currentPos << " | Score: " << p.score;
        return os;
    }
};

std::vector<Player> toVectorWithPlayers(std::vector<std::string> stringVectorPlayersStartingPositions)
{
	std::vector<Player> result;
	for (std::string stringVectorPlayerStartingPosition : stringVectorPlayersStartingPositions)
	{
		Player player;
		std::vector<std::string> splitted = StringParser::toVector(stringVectorPlayerStartingPosition, " ");
		player.playerNum = std::stoi(splitted[1]);
        player.currentPos = std::stoi(*splitted.rbegin());
        result.push_back(player);
	}
	return result;
}

long play(std::vector<Player> players, int diceSides, int winningScore)
{
	int timesDiceRolled = 0;
	int currentDiceSide = 0;
	std::set<int> playerPlayOrder;
	for (Player player : players)
	{
		playerPlayOrder.insert(player.playerNum);
	}
	int amountOfOtherPlayers = playerPlayOrder.size() - 1;
	std::set<int>::iterator currentPlayerPlay = playerPlayOrder.begin();
	while (std::find_if(players.begin(), players.end(), [](Player p){ return p.score >= 1000; }) == players.end())
	{
		int currentThrow = 0;
		// roll dice
		for (int i = 0; i < 3; i++)
		{
			timesDiceRolled++;
			currentDiceSide++;
			currentThrow += currentDiceSide;
			if (currentDiceSide == diceSides)
			{
				currentDiceSide = 0;
			}
		}
        
		int stepsToTake = currentThrow % 10;
		
		// current position
		Player& currentPlayer = *std::find_if(players.begin(), players.end(), [&](const Player & p){ return p.playerNum == *currentPlayerPlay; });
		int newPosition = currentPlayer.currentPos;
		// move player
		for (int i = 0; i < stepsToTake; i++)
		{
			newPosition++;
            if (newPosition > 10)
            {
                newPosition -= 10;
            }
		}
		currentPlayer.score += newPosition;
        currentPlayer.currentPos = newPosition;
		
		currentPlayerPlay++;
		if (currentPlayerPlay == playerPlayOrder.end())
		{
			currentPlayerPlay = playerPlayOrder.begin();
		}
	}
	
	return (*std::find_if(players.begin(), players.end(), [](const Player & p){ return p.score < 1000; })).score * timesDiceRolled;
}


// map which holds game state and outcome
std::map< std::tuple<int, int, int, int, int>, std::pair<long long, long long> > gameStateAndOutcome;
std::pair<long long, long long> getHowManyUniversesPlayerWins(std::vector<Player>& players, int& currentPlayerIndex, int diceSides, int winningScore)
{
    if (std::find_if(players.begin(), players.end(), [&](Player p){ return p.score >= winningScore; }) != players.end())
    {
        int winningPlayer = std::find_if(players.begin(), players.end(), [&](Player p){ return p.score >= winningScore; })->playerNum;
        return winningPlayer == 1 ? std::make_pair(1, 0) : std::make_pair(0, 1);
    }

    int otherPlayerIndex = currentPlayerIndex == 0 ? currentPlayerIndex + 1 : currentPlayerIndex - 1;
    if (gameStateAndOutcome.find(std::make_tuple(players[0].score, players[0].currentPos, players[1].score, players[1].currentPos, currentPlayerIndex)) != gameStateAndOutcome.end())
    {
        return gameStateAndOutcome[std::make_tuple(players[0].score, players[0].currentPos, players[1].score, players[1].currentPos, currentPlayerIndex)];
    }

    std::pair<long long, long long> outcome = std::make_pair(0, 0);
    for (int d1 = 1; d1 <= diceSides; d1++)
    {
        for (int d2 = 1; d2 <= diceSides; d2++)
        {
            for (int d3 = 1; d3 <= diceSides; d3++)
            {   
                std::vector<Player> playersBefore = players;
                int stepsToTake = (d1 + d2 + d3) % 10;
                Player& currentPlayer = players[currentPlayerIndex];   
                int newPosition = currentPlayer.currentPos;
                // move player
                for (int i = 0; i < stepsToTake; i++)
                {
                    newPosition++;
                    if (newPosition > 10)
                    {
                        newPosition -= 10;
                    }
                }
                currentPlayer.currentPos = newPosition;
                currentPlayer.score += newPosition;
                int currentPlayerIndexBefore = currentPlayerIndex;
                currentPlayerIndex = currentPlayerIndex == 0 ? currentPlayerIndex + 1 : currentPlayerIndex - 1;
                std::pair<long long, long long> result = getHowManyUniversesPlayerWins(players, currentPlayerIndex, diceSides, winningScore);
                outcome.first += result.first;
                outcome.second += result.second;
                players = playersBefore;
                currentPlayerIndex = currentPlayerIndexBefore;
            }
        }
    }
    otherPlayerIndex = currentPlayerIndex == 0 ? currentPlayerIndex + 1 : currentPlayerIndex - 1;
    gameStateAndOutcome[std::make_tuple(players[0].score, players[0].currentPos, players[1].score, players[1].currentPos, currentPlayerIndex)] = outcome;
    return outcome;
}

int main(void)
{
    std::vector<std::string> testInput = StringParser::toVector("Player 1 starting position: 4\nPlayer 2 starting position: 8", "\n");
    std::vector<Player> testVectorWithPlayers = toVectorWithPlayers(testInput);
    assert(play(toVectorWithPlayers(testInput), 100, 1000) == 739785);
    
    FileHandler fileHandler("input-files/2021/day21.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::vector<Player> vectorWithPlayers = toVectorWithPlayers(input);
    std::cout << "Day 21, puzzle 1: " << std::flush << play(vectorWithPlayers, 100, 1000) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    int startPlayerNumIndexTest = 0;
    std::pair<long long, long long> testResult = getHowManyUniversesPlayerWins(testVectorWithPlayers, startPlayerNumIndexTest, 3, 21);
    assert(std::max(testResult.first, testResult.second) == 444356092776315);
    t_begin = std::chrono::high_resolution_clock::now();    
    int startPlayerNumIndex = 0;
    std::pair<long long, long long> result = getHowManyUniversesPlayerWins(vectorWithPlayers, startPlayerNumIndex, 3, 21);
    std::cout << "Day 21, puzzle 2: " << std::flush << std::max(result.first, result.second) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
