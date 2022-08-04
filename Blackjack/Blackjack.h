#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Card.h"
#include "Player.h"

#include <algorithm>
#include <array>
#include <ctime>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

enum class Turn
{
	stand,
	hit,
};

class Blackjack
{
public:
	Blackjack();

public:
	bool play();

private:
	void check_house_win();
	void check_game_tie();
	void check_player_win();
	void check_remaining_cards();
	deck_type create_deck();
	bool get_game_state(uint8_t state);
	Card& give_card(Player& player);
	void house_turn();
	void player_turn();
	void print_controls();
	void print_current_hand();
	void print_game_summary();
	void print_hand(const hand_type& hand);
	void print_welcome();
	void reset_game();
	void set_game_state(uint8_t state);
	void set_game_states(const std::vector<uint8_t>& states);
	void shuffle_deck(deck_type& deck);
	void unset_game_state(uint8_t state);
	void unset_game_states(const std::vector<uint8_t>& states);

private:
	// Game constants
	static constexpr uint8_t m_total_cards{ 52 };
	static constexpr uint8_t m_maximum_score{ 21 };
	static constexpr uint8_t m_dealer_threshold{ 17 };
	static constexpr uint8_t m_default_card_value{ 2 };

	// Game state flags
	static constexpr uint8_t f_show_welcome_message{ 1 << 0 };
	static constexpr uint8_t f_game_over{ 1 << 1 };
	static constexpr uint8_t f_player_won{ 1 << 2 };
	static constexpr uint8_t f_game_tie{ 1 << 3 };

	index_type card_index{};
	deck_type deck{};
	uint8_t game_state{ f_show_welcome_message };
	Player house{};
	Player player{};
	int total_turns{ 0 };
};

#endif