#include "House.h"

// PUBLIC METHODS

int House::take_turn(const Card& card)
{
	while (points < 17)
	{
		take_card(card);
		points = get_hand_value();
	}

	return points;
}
