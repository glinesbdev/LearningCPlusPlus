#ifndef BLACKJACK_H
#define BLACKJACK_H

#ifndef TOTAL_CARDS
#define TOTAL_CARDS 52
#endif

#include "Card.h"
#include "House.h"
#include "Player.h"

#include <array>
#include <cassert>
#include <ctime>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using deck_type = std::array<Card, TOTAL_CARDS>;
using index_type = deck_type::size_type;

enum class Turn
{
	hit,
	stand,
};

class Blackjack
{
public:
	Blackjack();

public:
	bool did_player_win();
	bool play();

private:
	deck_type create_deck();
	Card give_card(Player& player);
	bool no_cards_remaining();
	void print_card(const Card& card);
	void print_controls();
	void print_deck(const deck_type& deck);
	void print_game_summary();
	void print_hand(const hand_type& hand);
	void print_welcome();
	void reset_game();
	void shuffle_deck(deck_type& deck);

private:
	index_type card_index;
	deck_type deck;
	bool game_over;
	House house;
	Player player;
	int total_turns;
};

#endif