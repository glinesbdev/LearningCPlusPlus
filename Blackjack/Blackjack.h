#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Card.h"
#include "Constants.h"
#include "Logger.h"
#include "Player.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <ctime>
#include <format>
#include <iostream>
#include <random>
#include <stdint.h>
#include <string>
#include <vector>

using deck_type = std::array<Card, 52>;
using hand_type = std::vector<Card>;
using index_type = deck_type::size_type;

enum class Turn
{
	stand,
	hit,
};

class Blackjack
{
public:
	Blackjack();

	// Copy policy
	Blackjack(const Blackjack& copy) = delete;
	Blackjack& operator=(const Blackjack& copy) = delete;

	// Move policy
	Blackjack(Blackjack&& move) = delete;
	Blackjack& operator=(Blackjack&& move) = delete;

	~Blackjack() = default;

	struct GameStats
	{
		int games_won;
		int games_lost;
		int games_tied;
	};

public:
	GameStats Play();

private:
	void checkHouseWin();
	void checkGameTie();
	void checkPlayerWin();
	void checkRemainingCards();
	deck_type createDeck();
	Card& giveCard(Player& player);
	bool hasGameState(std::byte state);
	void houseTurn();
	void playerTurn();
	void printControls();
	void printGameSummary();
	void printIntro();
	void resetGame();
	void setGameState(std::byte state);
	void setGameStates(const std::vector<std::byte>& states);
	void shuffleDeck(deck_type& deck);
	void unsetGameState(std::byte state);
	void unsetGameStates(const std::vector<std::byte>& states);

private:
	// Game constants
	static constexpr uint8_t m_totalCards{ 52 };
	static constexpr uint8_t m_dealerThreshold{ 17 };
	static constexpr uint8_t m_defaultCardValue{ 2 };

	// Game state flags
	static constexpr std::byte f_showIntroMessage{ 1 << 0 };
	static constexpr std::byte f_gameOver{ 1 << 1 };
	static constexpr std::byte f_playerWon{ 1 << 2 };
	static constexpr std::byte f_gameTie{ 1 << 3 };

	deck_type deck{};
	Player house{};
	Player player{};
	Logger logger{};
	index_type cardIndex{};
	int total_turns{ 0 };
	GameStats gameStats{};
	std::byte gameState{ f_showIntroMessage };
};

#endif