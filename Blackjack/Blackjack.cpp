#include "Blackjack.h"

// PUBLIC METHODS

Blackjack::Blackjack()
{
	reset_game();
}

Blackjack::GameStats Blackjack::play()
{
	if (get_game_state(f_show_welcome_message))
		print_welcome();

	std::cout << "House and Player have been delt\n";
	std::cout << std::format("You have {} points\n", player.get_points());
	player.print_hand();

	while (!get_game_state(f_game_over))
	{
		check_remaining_cards();
		player_turn();
		check_player_win();

		// prevent the game from continuing if the
		// game is already over
		if (get_game_state(f_game_over))
			continue;

		house_turn();
		check_house_win();

		// prevent the game from continuing if the
		// game is already over
		if (get_game_state(f_game_over))
			continue;

		std::cout << std::format("You have {} points\n", player.get_points());
		player.print_hand();
	}

	print_game_summary();

	std::cout << "Do you want to play again? Yes = 1, No = 0: ";
	int answer{};
	std::cin >> answer;

	if (answer)
	{
		unset_game_state(f_show_welcome_message);
		reset_game();
		play();
	}

	return game_stats;
}

// PRIVATE METHODS

void Blackjack::check_house_win()
{
	int house_points{ house.get_points() };

	if (house_points == m_maximum_score)
	{
		set_game_state(f_game_over);
	}
	else if (house_points > m_maximum_score)
	{
		set_game_states({ f_player_won, f_game_over });
	}

	check_game_tie();
}

void Blackjack::check_game_tie()
{
	if (get_game_state(f_game_over) && player.get_points() == house.get_points())
	{
		set_game_state(f_game_tie);
	}
}

void Blackjack::check_player_win()
{
	int player_points{ player.get_points() };
	int house_points{ house.get_points() };

	if (player_points == m_maximum_score)
	{
		set_game_states({ f_player_won, f_game_over });
	}
	else if (player_points > m_maximum_score)
	{
		set_game_state(f_game_over);
	}
	else if (get_game_state(f_game_over) && (house_points > m_maximum_score || (player_points <= m_maximum_score && player_points > house_points)))
	{
		set_game_state(f_player_won);
	}

	check_game_tie();
}

void Blackjack::check_remaining_cards()
{
	if (card_index >= m_total_cards)
	{
		set_game_state(f_game_over);
		check_player_win();
		check_house_win();
		std::cout << "No more cards!\n";
		print_game_summary();
	}
}

deck_type Blackjack::create_deck()
{
	deck_type new_deck{};
	index_type index{ 0 };

	for (int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suit); ++suit)
	{
		for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
		{
			new_deck[index].set_rank(static_cast<CardRank>(rank));
			new_deck[index].set_suit(static_cast<CardSuit>(suit));
			++index;
		}
	}

	return new_deck;
}

void Blackjack::house_turn()
{
	std::cout << "Dealer's turn\n";

	while (house.get_points() < m_dealer_threshold)
		give_card(house);
}

bool Blackjack::get_game_state(std::byte state)
{
	return static_cast<bool>(game_state & state);
}

Card& Blackjack::give_card(Player& p)
{
	Card& card{ deck[card_index] };
	p.take_card(card);
	++card_index;

	return card;
}

void Blackjack::player_turn()
{
	++total_turns;

	std::cout << "Your turn\n";
	print_controls();

	int input{ player.take_turn() };

	switch (input)
	{
		case static_cast<int>(Turn::stand):
		{
			set_game_state(f_game_over);
			break;
		}

		case static_cast<int>(Turn::hit):
		{
			give_card(player);
			check_player_win();
			break;
		}

		default:
		{
			std::cout << "\nUnrecognized choice\n\n";
			break;
		}
	}
}

void Blackjack::print_controls()
{
	std::cout << std::format("Hit = {}, Stand = {}: ", static_cast<int>(Turn::hit), static_cast<int>(Turn::stand));
}

void Blackjack::print_game_summary()
{
	if (get_game_state(f_player_won))
	{				 
		game_stats.games_won += 1;

		std::cout << "\n\n********************\n";
		std::cout << "*                  *\n";
		std::cout << "*    Player Won!   *\n";
		std::cout << "*                  *\n";
		std::cout << "********************\n\n";
	}
	else if (get_game_state(f_game_tie))
	{
		game_stats.games_tied += 1;

		std::cout << "\n\n********************\n";
		std::cout << "*                  *\n";
		std::cout << "*       Tie!       *\n";
		std::cout << "*                  *\n";
		std::cout << "********************\n\n";
	}
	else
	{
		game_stats.games_lost += 1;
		std::cout << "\n\n********************\n";
		std::cout << "*                  *\n";
		std::cout << "*    House Won!    *\n";
		std::cout << "*                  *\n";
		std::cout << "********************\n\n";
	}

	std::cout << "Player had these cards: ";
	player.print_hand();

	std::cout << std::format("Player had {} points\n", player.get_points());
	std::cout << std::format("House had {} points\n", house.get_points());
	std::cout << std::format("Game took {} turns to complete\n\n", total_turns);
}

void Blackjack::print_welcome()
{
	std::cout << "Welcome to Blackjack!\nInstructions: ";
	print_controls();
	std::cout << "\nGet the closest to 21 points as you can.\nIf you hit 21 points exactly, you win!\nHave less than the dealer when you choose to stand and you lose!\n";
}

void Blackjack::reset_game()
{
	// All the cards will be 2 points if the deck wasn't created yet.
	// Prevent a new deck from being created if the player plays more than 1 round.
	auto has_default_value
	{
		[](const Card& card)
		{
			return card.get_value() == m_default_card_value;
		}
	};

	if (std::all_of(std::begin(deck), std::end(deck), has_default_value))
		deck = create_deck();

	shuffle_deck(deck);

	unset_game_states({ f_game_over, f_player_won, f_game_tie });

	house = Player{};
	house.set_starting_hand(deck[0], deck[1]);
	check_house_win();

	player = Player{};
	player.set_starting_hand(deck[2], deck[3]);
	check_player_win();

	// next card after player and house has been delt
	card_index = 4;
	total_turns = 0;
}

void Blackjack::set_game_state(std::byte state)
{
	game_state |= state;
}

void Blackjack::set_game_states(const std::vector<std::byte>& states)
{
	std::for_each(states.begin(), states.end(), [this](std::byte state) { set_game_state(state); });
}

void Blackjack::shuffle_deck(deck_type& d)
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(std::begin(d), std::end(d), mt);
}

void Blackjack::unset_game_state(std::byte state)
{
	game_state &= ~state;
}

void Blackjack::unset_game_states(const std::vector<std::byte>& states)
{
	std::for_each(states.begin(), states.end(), [this](std::byte state) { unset_game_state(state); });
}
