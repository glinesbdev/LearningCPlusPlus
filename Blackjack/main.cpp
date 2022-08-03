#include "Blackjack.h"
#include <format>
#include <iostream>

int main()
{
	Blackjack game{};

	bool did_player_win{ game.play() };

	std::cout << std::boolalpha;
	std::cout << std::format("Did the player win? {}\n", did_player_win);

	return 0;
}