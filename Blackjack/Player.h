#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

#include <array>
#include <iostream>
#include <numeric>
#include <vector>

using hand_type = std::vector<Card>;

class Player
{
public:
	Player();

public:
	hand_type get_hand();
	int get_hand_value();
	int get_points();
	void get_starting_hand(const Card& first, const Card& second);
	void take_card(const Card& card);
	int take_turn();

private:
	void set_points();

private:
	hand_type hand;
	int input;
	int points;
};

#endif