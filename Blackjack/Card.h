#ifndef CARD_H
#define CARD_H

#include <cassert>
#include <iostream>

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
	CardRank get_rank() const;
	CardSuit get_suit() const;
	int get_value(int player_points = 0) const;
	void print() const;
	void set_rank(CardRank card_rank);
	void set_suit(CardSuit card_suit);

private:
	inline static constexpr const uint8_t m_maximum_value{21};
	inline static constexpr const uint8_t m_ace_high{11};
	inline static constexpr const uint8_t m_ace_low{1};

	int offset{ 2 - static_cast<int>(CardRank::rank_2) };

	CardRank rank{};
	CardSuit suit{};
};

#endif
