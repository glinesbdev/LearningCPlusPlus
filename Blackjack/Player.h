#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>

using hand_type = std::vector<Card>;

class Player
{
public:
	Player() = default;

	// Copy policy
	Player(const Player& copy) = delete;
	Player& operator=(const Player& copy) = delete;

	// Move policy
	Player(Player&& move) = delete;
	Player& operator=(Player&& move) = delete;

	~Player() = default;

public:
	hand_type GetHand();
	int GetPoints();
	void PrintHand();
	void Reset();
	void SetStartingHand(const Card& first, const Card& second);
	void TakeCard(const Card& card);
	int TakeTurn();

private:
	int getHandValue();
	void setPoints();

private:
	hand_type hand{};
	int input{};
	int points{};
	bool isDirty{ false };
};

#endif