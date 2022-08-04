#include "Blackjack.h"
#include <format>
#include <iostream>
#include <limits>

int main()
{
	Blackjack game{};
	Blackjack::GameStats stats{ game.play() };

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << std::format("\n***** Game Stats *****\nGames won: {}\nGames tied: {}\nGames lost: {}\n", stats.games_won, stats.games_tied, stats.games_lost);
	std::cout << "\nPress Enter to exit...";
	std::cin.get();

	return 0;
}