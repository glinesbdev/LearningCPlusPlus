#include "Blackjack.h"

// PUBLIC METHODS

Blackjack::Blackjack()
{
	set_game_state(f_show_welcome_message);
	reset_game();
}

bool Blackjack::play()
{
	if (get_game_state(f_show_welcome_message))
		print_welcome();

	std::cout << "House and Player have been delt.\n";
	std::cout << "You have " << player.get_points() << " points.\n";

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

		std::cout << "You have " << player.get_points() << " points.\n";
		std::cout << "Current cards: ";
		print_hand(player.get_hand());
		std::cout << '\n';
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

	return get_game_state(f_player_won);
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
		set_game_state(f_player_won);
		set_game_state(f_game_over);
	}

	check_game_tie();
}

void Blackjack::check_game_tie()
{
	int player_points{ player.get_points() };
	int house_points{ house.get_points() };

	if (get_game_state(f_game_over) && player_points == house_points)
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
		set_game_state(f_player_won);
		set_game_state(f_game_over);
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
			new_deck[index] = { static_cast<CardRank>(rank), static_cast<CardSuit>(suit) };
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

bool Blackjack::get_game_state(std::uint8_t state)
{
	return game_state & state;
}

Card Blackjack::give_card(Player& p)
{
	Card card{ deck[card_index] };
	p.take_card(card);
	++card_index;

	return card;
}

void Blackjack::player_turn()
{
	++total_turns;

	std::cout << "Your turn\n";
	print_controls();
	std::cout << '\n';

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
			std::cout << "Unrecognized choice\n";
			break;
		}
	}
}

void Blackjack::print_card(const Card& card)
{
	switch (card.rank)
	{
		case CardRank::rank_2:		std::cout << '2';	break;
		case CardRank::rank_3:		std::cout << '3';	break;
		case CardRank::rank_4:		std::cout << '4';	break;
		case CardRank::rank_5:		std::cout << '5';	break;
		case CardRank::rank_6:		std::cout << '6';	break;
		case CardRank::rank_7:		std::cout << '7';	break;
		case CardRank::rank_8:		std::cout << '8';	break;
		case CardRank::rank_9:		std::cout << '9';	break;
		case CardRank::rank_10:		std::cout << 'T';	break;
		case CardRank::rank_jack:	std::cout << 'J';	break;
		case CardRank::rank_queen:	std::cout << 'Q';	break;
		case CardRank::rank_king:	std::cout << 'K';	break;
		case CardRank::rank_ace:	std::cout << 'A';	break;
		default:
			std::cout << '?';
			break;
	}

	switch (card.suit)
	{
		case CardSuit::clubs:		std::cout << 'C';	break;
		case CardSuit::diamonds:	std::cout << 'D';	break;
		case CardSuit::hearts:		std::cout << 'H';	break;
		case CardSuit::spades:		std::cout << 'S';	break;
		default:
			std::cout << '?';
			break;
	}
}

void Blackjack::print_controls()
{
	std::cout << std::format("Hit = {}, Stand = {}", static_cast<int>(Turn::hit), static_cast<int>(Turn::stand));
}

void Blackjack::print_game_summary()
{
	std::cout << "\nGame over!\n";
	std::cout << "Player had " << player.get_points() << " points\n";
	std::cout << "House had " << house.get_points() << " points\n";
	std::cout << "Game took " << total_turns << " turn to complete\n";

	if (get_game_state(f_player_won))
		std::cout << "Player wins with " << player.get_points() << " points!\n";
	else if (get_game_state(f_game_tie))
		std::cout << "The game ended in a tie of " << player.get_points() << " points!\n";
	else
		std::cout << "House wins with " << house.get_points() << " points!\n";
}

void Blackjack::print_hand(const hand_type& hand)
{
	for (auto& card : hand)
	{
		print_card(card);
		std::cout << ' ';
	}
}

void Blackjack::print_welcome()
{
	std::cout << "Welcome to Blackjack!\n";
	std::cout << "Instructions: ";
	print_controls();
	std::cout << "\nGet the closest to 21 points as you can.\nIf you hit 21 points exactly, you win!\nHave less than the dealer when you choose to stand and you lose!\n";
}

void Blackjack::reset_game()
{
	// All the cards will be 2 points if the deck wasn't created yet.
	// Prevent a new deck from being created if the player plays more than 1 round.
	if (std::all_of(std::begin(deck), std::end(deck), [](Card& card) { return card.get_value() == 2; }))
		deck = create_deck();

	shuffle_deck(deck);

	unset_game_state(f_game_over);
	unset_game_state(f_player_won);
	unset_game_state(f_game_tie);

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

void Blackjack::set_game_state(std::uint8_t state)
{
	game_state |= state;
}

void Blackjack::shuffle_deck(deck_type& d)
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(std::begin(d), std::end(d), mt);
}

void Blackjack::unset_game_state(uint8_t state)
{
	game_state &= ~state;
}
