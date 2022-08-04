#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Card.h"
#include "Player.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <ctime>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using deck_type = std::array<Card, 52>;
using hand_type = std::vector<Card>;
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

	struct GameStats
	{
		int games_won;
		int games_lost;
		int games_tied;
	};

public:
	GameStats play();

private:
	void check_house_win();
	void check_game_tie();
	void check_player_win();
	void check_remaining_cards();
	deck_type create_deck();
	Card& give_card(Player& player);
	bool has_game_state(std::byte state);
	void house_turn();
	void player_turn();
	void print_controls();
	void print_game_summary();
	void print_welcome();
	void reset_game();
	void set_game_state(std::byte state);
	void set_game_states(const std::vector<std::byte>& states);
	void shuffle_deck(deck_type& deck);
	void unset_game_state(std::byte state);
	void unset_game_states(const std::vector<std::byte>& states);

private:
	// Game constants
	inline static constexpr const uint8_t m_total_cards{ 52 };
	inline static constexpr const uint8_t m_maximum_score{ 21 };
	inline static constexpr const uint8_t m_dealer_threshold{ 17 };
	inline static constexpr const uint8_t m_default_card_value{ 2 };

	// Game state flags
	inline static constexpr const std::byte f_show_welcome_message{ 1 << 0 };
	inline static constexpr const std::byte f_game_over{ 1 << 1 };
	inline static constexpr const std::byte f_player_won{ 1 << 2 };
	inline static constexpr const std::byte f_game_tie{ 1 << 3 };

	deck_type deck{};
	Player house;
	Player player;
	index_type card_index{};
	int total_turns{ 0 };
	GameStats game_stats{};
	std::byte game_state{ f_show_welcome_message };
};

#endif