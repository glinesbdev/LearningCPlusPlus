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

struct Card
{
public:
	CardRank rank{};
	CardSuit suit{};

	int get_value(int player_points = 0) const
	{
		assert((rank >= CardRank::rank_2 || rank <= CardRank::max_ranks) && "Error: invalid card rank");

		if (rank < CardRank::rank_jack)
		{
			return static_cast<int>(rank) + offset;
		}
		else if (rank == CardRank::rank_ace)
		{
			if (player_points + m_ace_high > m_maximum_value)
				return m_ace_low;

			return m_ace_high;
		}

		return 10;
	}

	void print() const
	{
		assert((rank >= CardRank::rank_2 || rank <= CardRank::max_ranks) && "Error: invalid card rank");

		switch (rank)
		{
			case CardRank::rank_2:		std::cout << '2';	break;
			case CardRank::rank_3:		std::cout << '3';	break;
			case CardRank::rank_4:		std::cout << '4';	break;
			case CardRank::rank_5:		std::cout << '5';	break;
			case CardRank::rank_6:		std::cout << '6';	break;
			case CardRank::rank_7:		std::cout << '7';	break;
			case CardRank::rank_8:		std::cout << '8';	break;
			case CardRank::rank_9:		std::cout << '9';	break;
			case CardRank::rank_10:		std::cout << 'T';	break;
			case CardRank::rank_jack:	std::cout << 'J';	break;
			case CardRank::rank_queen:	std::cout << 'Q';	break;
			case CardRank::rank_king:	std::cout << 'K';	break;
			case CardRank::rank_ace:	std::cout << 'A';	break;
			default:
				std::cout << '?';
				break;
		}

		switch (suit)
		{
			case CardSuit::clubs:		std::cout << 'C';	break;
			case CardSuit::diamonds:	std::cout << 'D';	break;
			case CardSuit::hearts:		std::cout << 'H';	break;
			case CardSuit::spades:		std::cout << 'S';	break;
			default:
				std::cout << '?';
				break;
		}
	}

private:
	static constexpr uint8_t m_maximum_value{21};
	static constexpr uint8_t m_ace_high{11};
	static constexpr uint8_t m_ace_low{1};

	int offset{ 2 - static_cast<int>(CardRank::rank_2) };
};

#endif
