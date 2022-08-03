#ifndef CARD_H
#define CARD_H

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
	CardRank rank{};
	CardSuit suit{};

	int get_value(int player_points)
	{
		switch (rank)
		{
			case CardRank::rank_2:		return 2;
			case CardRank::rank_3:		return 3;
			case CardRank::rank_4:		return 4;
			case CardRank::rank_5:		return 5;
			case CardRank::rank_6:		return 6;
			case CardRank::rank_7:		return 7;
			case CardRank::rank_8:		return 8;
			case CardRank::rank_9:		return 9;
			case CardRank::rank_10:		return 10;
			case CardRank::rank_jack:	return 10;
			case CardRank::rank_queen:	return 10;
			case CardRank::rank_king:	return 10;
			case CardRank::rank_ace:
			{
				if (player_points + 11 > 21)
					return 1;

				return 11;
			}
			default:					return 0;
		}
	}
};

#endif
