#include "player.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ariel;
Player::Player(string name) : name(std::move(name))
{
    cardsTaken = 0;
    isPlaying = false;
}
int Player::cardesTaken()
{
    return this->cardsTaken;
}
bool Player::getIsPlaying()
{
    return this->isPlaying;
}
int Player::stacksize()
{
    return player_stack.size();
}
void Player::setPlaying(bool bool1)
{
    this->isPlaying = bool1;
}
void Player::addCard(Card card_to_add)
{
    this->player_stack.push_back(card_to_add);
}
Card Player::pullCard()
{
    if (player_stack.empty())
    {
        // handle error or return a default card value
        // depending on your program's logic
        return NULL;
    }
    else
    {
        Card lastCard = player_stack.back();
        player_stack.pop_back();
        return lastCard;
    }
}
string Player::getName()
{
    return this->name;
}
void Player::setCardsTaken(int num)
{
    this->cardsTaken = num;
}
