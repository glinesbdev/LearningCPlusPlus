#include "Blackjack.h"

// PUBLIC METHODS

Blackjack::Blackjack()
{
	resetGame();
}

Blackjack::GameStats Blackjack::Play()
{
	if (hasGameState(f_showIntroMessage))
		printIntro();

	std::cout << "House and Player have been delt\n";
	std::cout << std::format("You have {} points\n", player.GetPoints());
	player.PrintHand();

	while (!hasGameState(f_gameOver))
	{
		checkRemainingCards();
		playerTurn();
		checkPlayerWin();

		// prevent the game from continuing if the
		// game is already over
		if (hasGameState(f_gameOver))
			continue;

		houseTurn();
		checkHouseWin();

		// prevent the game from continuing if the
		// game is already over
		if (hasGameState(f_gameOver))
			continue;

		std::cout << std::format("You have {} points\n", player.GetPoints());
		player.PrintHand();
	}

	printGameSummary();

	std::cout << "Do you want to play again? Yes = 1, No = 0: ";
	int answer{};
	std::cin >> answer;

	if (answer)
	{
		house.Reset();
		player.Reset();
		unsetGameState(f_showIntroMessage);
		resetGame();
		Play();
	}

	return gameStats;
}

// PRIVATE METHODS

void Blackjack::checkHouseWin()
{
	int house_points{ house.GetPoints() };

	if (house_points == constants::m_maximumScore)
	{
		setGameState(f_gameOver);
	}
	else if (house_points > constants::m_maximumScore)
	{
		setGameStates({ f_playerWon, f_gameOver });
	}
	else
	{
		checkGameTie();
	}
}

void Blackjack::checkGameTie()
{
	if (hasGameState(f_gameOver) && player.GetPoints() == house.GetPoints())
	{
		setGameState(f_gameTie);
	}
}

void Blackjack::checkPlayerWin()
{
	int player_points{ player.GetPoints() };
	int house_points{ house.GetPoints() };

	if (player_points == constants::m_maximumScore)
	{
		setGameStates({ f_playerWon, f_gameOver });
	}
	else if (player_points > constants::m_maximumScore)
	{
		setGameState(f_gameOver);
	}
	else if (hasGameState(f_gameOver) && (house_points > constants::m_maximumScore || (player_points <= constants::m_maximumScore && player_points > house_points)))
	{
		setGameState(f_playerWon);
	}
	else
	{
		checkGameTie();
	}
}

void Blackjack::checkRemainingCards()
{
	if (cardIndex >= m_totalCards)
	{
		setGameState(f_gameOver);
		checkPlayerWin();
		checkHouseWin();
		std::cout << "No more cards!\n";
		printGameSummary();
	}
}

deck_type Blackjack::createDeck()
{
	deck_type new_deck{};
	index_type index{ 0 };

	for (int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suit); ++suit)
	{
		for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
		{
			new_deck[index].SetRank(static_cast<CardRank>(rank));
			new_deck[index].SetSuit(static_cast<CardSuit>(suit));
			++index;
		}
	}

	return new_deck;
}

bool Blackjack::hasGameState(std::byte state)
{
	return static_cast<bool>(gameState & state);
}

void Blackjack::houseTurn()
{
	std::cout << "Dealer's turn\n";

	while (house.GetPoints() < m_dealerThreshold)
		giveCard(house);
}

Card& Blackjack::giveCard(Player& p)
{
	Card& card{ deck[cardIndex] };
	p.TakeCard(card);
	++cardIndex;

	return card;
}

void Blackjack::playerTurn()
{
	++total_turns;

	std::cout << "Your turn\n";
	printControls();

	int input{ player.TakeTurn() };

	switch (input)
	{
		case static_cast<int>(Turn::stand):
		{
			setGameState(f_gameOver);
			break;
		}

		case static_cast<int>(Turn::hit):
		{
			giveCard(player);
			checkPlayerWin();
			break;
		}

		default:
		{
			std::cout << "\nUnrecognized choice\n\n";
			break;
		}
	}
}

void Blackjack::printControls()
{
	std::cout << std::format("Hit = {}, Stand = {}: ", static_cast<int>(Turn::hit), static_cast<int>(Turn::stand));
}

void Blackjack::printGameSummary()
{
	if (hasGameState(f_playerWon))
	{				 
		gameStats.games_won += 1;

		std::cout << "\n\n********************\n";
		std::cout << "*                  *\n";
		std::cout << "*    Player Won!   *\n";
		std::cout << "*                  *\n";
		std::cout << "********************\n\n";
	}
	else if (hasGameState(f_gameTie))
	{
		gameStats.games_tied += 1;

		std::cout << "\n\n********************\n";
		std::cout << "*                  *\n";
		std::cout << "*       Tie!       *\n";
		std::cout << "*                  *\n";
		std::cout << "********************\n\n";
	}
	else
	{
		gameStats.games_lost += 1;

		std::cout << "\n\n********************\n";
		std::cout << "*                  *\n";
		std::cout << "*    House Won!    *\n";
		std::cout << "*                  *\n";
		std::cout << "********************\n\n";
	}

	player.PrintHand();

	std::cout << std::format("Player had {} points\n", player.GetPoints());
	std::cout << std::format("House had {} points\n", house.GetPoints());
	std::cout << std::format("Game took {} turns to complete\n\n", total_turns);
}

void Blackjack::printIntro()
{
	std::cout << "Welcome to Blackjack!\nInstructions: ";
	printControls();
	std::cout << "\nGet the closest to 21 points as you can.\nIf you hit 21 points exactly, you win!\nHave less than the dealer when you choose to stand and you lose!\n";
}

void Blackjack::resetGame()
{
	// All the cards will be 2 points if the deck wasn't created yet.
	// Prevent a new deck from being created if the player plays more than 1 round.
	auto has_default_value
	{
		[](const Card& card)
		{
			return card.GetValue() == m_defaultCardValue;
		}
	};

	if (std::all_of(std::begin(deck), std::end(deck), has_default_value))
		deck = createDeck();

	shuffleDeck(deck);
	unsetGameStates({ f_gameOver, f_playerWon, f_gameTie });

	house.SetStartingHand(deck[0], deck[1]);
	checkHouseWin();

	player.SetStartingHand(deck[2], deck[3]);
	checkPlayerWin();

	// next card after player and house has been delt
	cardIndex = 4;
	total_turns = 0;
}

void Blackjack::setGameState(std::byte state)
{
	gameState |= state;
}

void Blackjack::setGameStates(const std::vector<std::byte>& states)
{
	std::for_each(states.begin(), states.end(), [this](std::byte state) { setGameState(state); });
}

void Blackjack::shuffleDeck(deck_type& d)
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(std::begin(d), std::end(d), mt);
}

void Blackjack::unsetGameState(std::byte state)
{
	gameState &= ~state;
}

void Blackjack::unsetGameStates(const std::vector<std::byte>& states)
{
	std::for_each(states.begin(), states.end(), [this](std::byte state) { unsetGameState(state); });
}
