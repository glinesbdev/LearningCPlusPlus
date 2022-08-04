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
	hand_type get_hand();
	int get_points();
	void print_hand();
	void set_starting_hand(const Card& first, const Card& second);
	void take_card(const Card& card);
	int take_turn();

private:
	int get_hand_value();
	void set_points();

private:
	hand_type hand{};
	int input{};
	int points{};
};

#endif