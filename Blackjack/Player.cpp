#include "Player.h"

// PUBLIC METHODS

int Player::get_points()
{
    return points;
}

void Player::print_hand()
{
    std::cout << "Current cards: ";

    for (auto& card : get_hand())
    {
        card.print();
        std::cout << ' ';
    }

    std::cout << '\n';
}

hand_type Player::get_hand()
{
    // Sort the cards from lowest rank to highest
    // so that the ace is calculated properly against
    // the points the player currently has.
    std::sort(hand.begin(), hand.end(), [](const Card& lhs, const Card& rhs) { return lhs.get_rank() < rhs.get_rank(); });

    return hand;
}

void Player::set_starting_hand(const Card& first, const Card& second)
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

// PRIVATE METHODS

int Player::get_hand_value()
{
    int result{};

    for (auto& card : get_hand())
    {
        result += card.get_value(points);
    }

    return result;
}

void Player::set_points()
{
    points = get_hand_value();
}