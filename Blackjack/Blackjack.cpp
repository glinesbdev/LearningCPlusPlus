#include "Blackjack.h"

// PUBLIC METHODS

Blackjack::Blackjack()
{
	reset_game();
}

bool Blackjack::did_player_win()
{
	int player_points{ player.get_points() };
	return game_over && player_points <= 21 && player_points > house.get_points();
}

bool Blackjack::play()
{
	print_welcome();

	while (!game_over)
	{
		++total_turns;

		if (no_cards_remaining())
		{
			game_over = true;
			continue;
		}

		int input{ player.take_turn() };

		switch (input)
		{
			case static_cast<int>(Turn::hit):
			{
				give_card(player);
				break;
			}
			case static_cast<int>(Turn::stand):
			{
				game_over = true;
				continue;
			}
			default:
			{
				std::cout << "Unrecognized input\n";
				print_controls();
				continue;
			}
		}

		int player_points{ player.get_points() };

		if (player_points > 21)
		{
			game_over = true;
			std::cout << "Player has gone over 21 points!\n";
			continue;
		}
		else if (did_player_win())
		{
			game_over = true;
			std::cout << "Player win!\n";
			continue;
		}
		else
		{
			std::cout << "You have " << player_points << " points.\n";
			std::cout << "Current cards: ";
			print_hand(player.get_hand());
		}

		std::cout << "\nDealer's turn\n";

		while (house.get_points() < 17)
		{
			give_card(house);
			int house_points{ house.get_points() };

			if (house_points == 21)
			{
				game_over = true;
				std::cout << "House wins with 21 points!\n";
			}
			else if (house_points > 21)
			{
				game_over = true;
				std::cout << "House has gone over 21 points!\n";
			}
		}
	}

	print_game_summary();

	std::cout << "Do you want to play again? Yes = 1, No = 0: ";
	int answer{};
	std::cin >> answer;

	if (answer > 0)
	{
		reset_game();
		play();
	}

	return did_player_win();
}

// PRIVATE METHODS

deck_type Blackjack::create_deck()
{
	deck_type newDeck{};
	index_type index{ 0 };

	for (int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suit); ++suit)
	{
		for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
		{
			newDeck[index] = { static_cast<CardRank>(rank), static_cast<CardSuit>(suit) };
			++index;
		}
	}

	return newDeck;
}

Card Blackjack::give_card(Player& p)
{
	Card card{ deck[card_index] };
	p.take_card(card);
	++card_index;

	return card;
}

bool Blackjack::no_cards_remaining()
{
	if (card_index >= TOTAL_CARDS)
	{
		std::cout << "Game over!\n";
		print_game_summary();

		return true;
	}

	return false;
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

void Blackjack::print_deck(const deck_type& d)
{
	for (std::size_t i{ 0 }; i < d.size(); ++i)
	{
		print_card(d[i]);
		std::cout << ' ';
	}

	std::cout << '\n';
}

void Blackjack::print_game_summary()
{
	std::cout << "Player had " << player.get_points() << " points\n";
	std::cout << "House had " << house.get_points() << " points\n";
	std::cout << "Game took " << total_turns << " turn to complete\n";

	if (did_player_win())
	{
		std::cout << "Player wins with " << player.get_points() << " points!\n";
	}
	else
	{
		std::cout << "House wins with " << house.get_points() << " points!\n";
	}
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
	std::cout << "House and Player have been delt.\n";
	std::cout << "You have " << player.get_points() << " points.\n";
}

void Blackjack::reset_game()
{
	deck = create_deck();
	shuffle_deck(deck);

	house = House{};
	house.get_starting_hand(deck[0], deck[1]);

	player = Player{};
	player.get_starting_hand(deck[2], deck[3]);

	// next card after player and house has been delt
	card_index = 4;
	game_over = false;
	total_turns = 0;
}

void Blackjack::shuffle_deck(deck_type& d)
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(std::begin(d), std::end(d), mt);
}
