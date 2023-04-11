#include "player.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ariel;
/**
 * @brief Construct a new Player, reseting cardsTaken and isPLaying.
 *
 * @param name
 */
Player::Player(string name) : name(std::move(name))
{
    cardsTaken = 0;
    isPlaying = false;
}
/**
 * @brief getter for cardsTaken
 *
 * @return int cards player taken
 */
int Player::cardesTaken()
{
    return this->cardsTaken;
}
/**
 * @brief getter for isPlaying
 *
 * @return true if playing
 * @return false if not playing
 */
bool Player::getIsPlaying()
{
    return this->isPlaying;
}
/**
 * @brief getter for player's deck size
 *
 * @return player's deck size
 */
int Player::stacksize()
{
    return player_stack.size();
}
/**
 * @brief set if a player is playing
 *
 * @param isPlayin if a player playing
 */
void Player::setPlaying(bool isPlayin)
{
    this->isPlaying = isPlayin;
}
/**
 * @brief adds a card to player's deck
 *
 * @param card_to_add
 */
void Player::addCard(Card card_to_add)
{
    this->player_stack.push_back(card_to_add);
}
/**
 * @brief draw a card from player's deck.
 *
 * @return Card
 */
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
/**
 * @brief name getter
 *
 * @return string
 */
string Player::getName()
{
    return this->name;
}
/**
 * @brief cards taken setter
 *
 * @param num
 */
void Player::setCardsTaken(int num)
{
    this->cardsTaken = num;
}
