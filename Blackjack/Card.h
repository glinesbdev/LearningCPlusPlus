#ifndef CARD_H
#define CARD_H

#include "Constants.h"

#include <cassert>
#include <iostream>
#include <stdint.h>

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,
	max_ranks,
};

enum class CardSuit
{
	clubs,
	diamonds,
	hearts,
	spades,
	max_suit,
};

class Card
{
public:
	CardRank GetRank() const;
	CardSuit GetSuit() const;
	int GetValue(int player_points = 0) const;
	void Print() const;
	void SetRank(CardRank card_rank);
	void SetSuit(CardSuit card_suit);

private:
	static constexpr uint8_t m_aceHigh{ 11 };
	static constexpr uint8_t m_aceLow{1};

	int offset{ 2 - static_cast<int>(CardRank::rank_2) };

	CardRank rank{};
	CardSuit suit{};
};

#endif
