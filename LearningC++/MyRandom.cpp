#include "MyRandom.h"

inline unsigned int get_random()
{
	std::mt19937 mt;
	return mt();
}