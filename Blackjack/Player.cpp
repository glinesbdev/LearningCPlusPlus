#include "Player.h"

// PUBLIC METHODS

Player::Player()
{
    hand = {};
    input = 0;
    points = 0;
}
int Player::get_points()
{
    return points;
}

hand_type Player::get_hand()
{
    return hand;
}

void Player::get_starting_hand(const Card& first, const Card& second)
{
    hand = { first, second };
    points = get_hand_value();
}

void Player::take_card(const Card& card)
{
    hand.push_back(card);
    set_points();
}

int Player::take_turn()
{
    std::cin >> input;

    return input;
}

int Player::get_hand_value()
{
    int result{};

    for (auto& card : hand)
    {
        result += card.get_value();
    }

    return result;
}

// PRIVATE METHODS

void Player::set_points()
{
    points = get_hand_value();
}