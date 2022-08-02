#ifndef HOUSE_H
#define HOUSE_H

#include "Player.h"

class House : public Player
{
public:
	int take_turn(const Card& card);
};

#endif