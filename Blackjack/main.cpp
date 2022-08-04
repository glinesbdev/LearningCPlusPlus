#include "Blackjack.h"
#include <format>
#include <iostream>

int main()
{
	Blackjack game{};
	Blackjack::GameStats stats{ game.play() };

	std::cout << std::format("***** Game Stats *****\nGames won: {}\nGames tied: {}\nGames lost: {}\n", stats.games_won, stats.games_tied, stats.games_lost);

	return 0;
}