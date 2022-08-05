#include "Player.h"

// PUBLIC METHODS

int Player::GetPoints()
{
    return points;
}

void Player::PrintHand()
{
    std::cout << "Current cards: ";

    for (auto& card : GetHand())
    {
        card.Print();
        std::cout << ' ';
    }

    std::cout << '\n';
}

void Player::Reset()
{
    if (isDirty)
    {
        points = 0;
        isDirty = false;
    }
}

hand_type Player::GetHand()
{
    // Sort the cards from lowest rank to highest
    // so that the ace is calculated properly against
    // the points the player currently has.
    std::sort(hand.begin(), hand.end(), [](const Card& lhs, const Card& rhs) { return lhs.GetRank() < rhs.GetRank(); });

    return hand;
}

void Player::SetStartingHand(const Card& first, const Card& second)
{
    hand = { first, second };
    setPoints();
}

void Player::TakeCard(const Card& card)
{
    hand.push_back(card);
    setPoints();
}

int Player::TakeTurn()
{
    std::cin >> input;

    return input;
}

// PRIVATE METHODS

int Player::getHandValue()
{
    int result{};

    for (auto& card : GetHand())
    {
        result += card.GetValue(points);
    }

    return result;
}

void Player::setPoints()
{
    points = getHandValue();
    isDirty = true;
}