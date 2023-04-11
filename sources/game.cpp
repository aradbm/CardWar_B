#include "game.hpp"
#include "player.hpp"
#include <iostream>
#include <algorithm> // For std::shuffle
#include <random>
using namespace ariel;
using namespace std;
/**
 * @brief Create a and shuffle deck object
 * @param deck
 * @param size
 */
void create_and_shuffle_deck(Card deck[], int size)
{
    for (size_t i = 0; i < 52; i++)
    {
        deck[i] = Card((i % 13) + 1, (i % 4) + 1);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck, deck + size, g);
}
/**
 * @brief Construct a new Game:: Game object
 *
 * @param player1
 * @param player2
 */
Game::Game(Player &player1, Player &player2)
    : pl1(player1), pl2(player2)
{
    num_of_turns = 0;
    num_of_draws = 0;
    p1_turns_won = 0;
    if (player1.getIsPlaying() || player2.getIsPlaying())
    {
        throw string("One of the players is in a game! wait untill he ends.");
    }

    else
    {
        this->pl1 = player1;
        this->pl2 = player2;
        pl1.setPlaying(true);
        pl2.setPlaying(true);
        pl1.setCardsTaken(0);
        pl2.setCardsTaken(0);
        Card deck[52];
        create_and_shuffle_deck(deck, 52);
        for (size_t i = 0; i < 52; i++) // setting the decks for the players
        {
            if (i < 26)
                pl1.addCard(deck[i]);
            else
                pl2.addCard(deck[i]);
        }
    }
}
/**
 * @brief play turn untill there are no more cards in hands of both players.
 *
 */
void Game::playAll()
{
    while (pl1.stacksize() != 0)
    {
        playTurn();
    }
}
/**
 * @brief play a turn in game.
 *
 */
void Game::playTurn()
{
    if (&pl1 == &pl2)
    {
        throw runtime_error("Can't make a game with the same player!");
    }
    string turn = "";
    vector<Card> p1war;
    vector<Card> p2war;
    this->num_of_turns++;
    if (this->pl1.stacksize() == 0)
    {
        throw string("The game played out, cant play anymore.");
        return;
    }
    Card p1c = this->pl1.pullCard();
    Card p2c = this->pl2.pullCard();
    while (p1c.getNum() == p2c.getNum())
    {
        num_of_draws++;
        if (pl1.stacksize() < 2)
        {
            while (!p1war.empty())
            {
                Card lastCard = p1war.back();
                p1war.pop_back();
                pl1.addCard(lastCard);
            }
            while (!p2war.empty())
            {
                Card lastCard = p2war.back();
                p2war.pop_back();
                pl1.addCard(lastCard);
            }
            return;
        }
        p1war.push_back(p1c);
        p1war.push_back(pl1.pullCard());
        p2war.push_back(p2c);
        p2war.push_back(pl2.pullCard());
        turn += pl1.getName() + " played " + p1c.toString() + " " + pl2.getName() + " played " +
                p2c.toString() + ".";
        turn += "draw. ";
        p1c = this->pl1.pullCard();
        p2c = this->pl2.pullCard();
    }
    turn += pl1.getName() + " played " + p1c.toString() + " " + pl2.getName() + " played " +
            p2c.toString() + ".";
    p1war.push_back(p1c);
    p2war.push_back(p2c);

    // cout << turn << endl;
    string winnerName = "";
    if (p1c.getNum() > p2c.getNum())
    {
        if (p2c.getNum() == 1 && p1c.getNum() != 2) // player 2 won this turn
            winnerName = pl2.getName();
        else
        {
            p1_turns_won++;
            winnerName = pl1.getName();
        }
    }
    else
    {
        if (p1c.getNum() == 1 && p2c.getNum() != 2) // player 1 won this turn
        {
            p1_turns_won++;
            winnerName = pl1.getName();
        }
        else
            winnerName = pl2.getName();
    }
    if (winnerName == pl1.getName())
    {
        pl1.setCardsTaken(pl1.cardesTaken() + (int)p1war.size() + (int)p2war.size());
        turn += " " + pl1.getName() + " wins.";
    }
    else
    {
        pl2.setCardsTaken(pl2.cardesTaken() + (int)p1war.size() + (int)p2war.size());
        turn += " " + pl2.getName() + " wins.";
    }

    game_log.push_back(turn + "\n");
}
/**
 * @brief printing the last turn in the game. print if can't.
 *
 */
void Game::printLastTurn()
{
    if (!game_log.empty())
        cout << game_log.back() << endl;
    else
        cout << "A turn hasn't been made yet!" << endl;
}
/**
 * @brief print who is the winner. Doesn't print if game not over yet.
 *
 */
void Game::printWiner()
{
    int p1_cards = this->pl1.cardesTaken();
    int p2_cards = this->pl2.cardesTaken();
    if (p1_cards + p2_cards < 52)
    {
        cout << "game not over yet!" << endl;
    }
    else
    {
        if (p1_cards > p2_cards)
            cout << "Player 1 won" << endl;
        else if (p1_cards < p2_cards)
            cout << "Player 2 won" << endl;
        else
            cout << "Tie!" << endl;
        pl1.setPlaying(false);
        pl2.setPlaying(false);
    }
}
/**
 * @brief print all the game log untill now.
 *
 */
void Game::printLog()
{
    for (auto i : game_log)
    {
        cout << i;
    }
}
/**
 * @brief printing for each player prints basic statistics: win rate, cards won.
 * Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
 *
 */
void Game::printStats()
{
    cout << pl1.getName() << " has a win rate of: " << (double)(p1_turns_won) / (double)num_of_turns << ", and won " << pl1.cardesTaken() << " cards" << endl;
    cout << pl2.getName() << " has a win rate of: " << 1 - (double)p1_turns_won / (double)(num_of_turns) << ", and won " << pl2.cardesTaken() << " cards" << endl;
    cout << "Number of draws:  " << num_of_draws << ", draw rate:" << (double)num_of_draws / (double)num_of_turns << endl;
}