#include "Blackjack.h"
#include <iostream>

int main()
{
	Blackjack game{};

	bool did_player_win{ game.play() };

	std::cout << std::boolalpha;
	std::cout << "Did the player win? " << did_player_win << '\n';

	return 0;
}