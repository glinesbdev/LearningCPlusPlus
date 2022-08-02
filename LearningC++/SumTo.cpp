#include "SumTo.h"

const int sumTo(const int value)
{
	int answer{ 0 };

	for (int i{ 1 }; i <= value; i++)
	{
		answer += i;
	}

	return answer;
}