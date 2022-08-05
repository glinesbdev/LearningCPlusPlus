#include "Card.h"

CardRank Card::GetRank() const
{
	return rank;
}

CardSuit Card::GetSuit() const
{
	return suit;
}

int Card::GetValue(int player_points) const
{
	assert((rank >= CardRank::rank_2 || rank <= CardRank::max_ranks) && "Error: invalid card rank");

	if (rank < CardRank::rank_jack)
	{
		return static_cast<int>(rank) + offset;
	}
	else if (rank == CardRank::rank_ace)
	{
		if (player_points + m_aceHigh > constants::m_maximumScore)
			return m_aceLow;

		return m_aceHigh;
	}

	// 10, Jack, Queen, and King cards all have the value of 10
	return 10;
}

void Card::Print() const
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

void Card::SetRank(CardRank card_rank)
{
	rank = card_rank;
}

void Card::SetSuit(CardSuit card_suit)
{
	suit = card_suit;
}
