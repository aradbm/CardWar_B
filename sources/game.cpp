#include "game.hpp"
#include "player.hpp"
#include <iostream>
#include <algorithm> // For std::shuffle
#include <random>
using namespace ariel;
using namespace std;

void create_and_shuffle_deck(Card deck[], int size)
{
    for (size_t i = 0; i < 52; i++)
    {
        deck[i] = Card((i % 13) + 1, (i % 4) + 1);
    }
    std::random_device rd; // A random number source
    std::mt19937 g(rd());  // A random number engine
    // Shuffle the deck using the random number generator
    std::shuffle(deck, deck + size, g);
}

Game::Game(Player player1, Player player2) : p1_turns_won(0), num_of_turns(0)
{
    if (player1.getIsPlaying() || player2.getIsPlaying())
    {
        throw string("One of the players is in a game! wait untill he ends.");
    }
    if (&player1 == &player2)
    {
        cout << "Can't make a game with the same player!" << endl;
        exit(1);
    }
    else
    {
        this->p1 = player1;
        this->p2 = player2;
        p1.setPlaying(true);
        p2.setPlaying(true);
        Card deck[52];
        create_and_shuffle_deck(deck, 52);
        for (size_t i = 0; i < 52; i++) // setting the decks for the players
        {
            if (i < 26)
                p1.addCard(deck[i]);
            else
                p2.addCard(deck[i]);
        }
    }
}

Game::~Game()
{
    game_log.clear();
}
void Game::playAll()
{
    while (p1.stacksize() != 0)
    {
        playTurn();
    }
}
void Game::playTurn()
{
    string turn = "";
    vector<Card> p1war;
    vector<Card> p2war;
    this->num_of_turns++;
    if (this->p1.stacksize() == 0)
    {
        throw string("The game played out, cant play anymore.");
        return;
    }
    Card p1c = this->p1.pullCard();
    Card p2c = this->p2.pullCard();
    while (p1c.getNum() == p2c.getNum())
    {
        if (p1.stacksize() < 2)
        {
            while (!p1war.empty())
            {
                Card lastCard = p1war.back();
                p1war.pop_back();
                p1.addCard(lastCard);
            }
            while (!p2war.empty())
            {
                Card lastCard = p2war.back();
                p2war.pop_back();
                p1.addCard(lastCard);
            }
            return;
        }
        p1war.push_back(p1c);
        p1war.push_back(p1.pullCard());
        p2war.push_back(p2c);
        p2war.push_back(p2.pullCard());
        turn += p1.getName() + " played " + p1c.toString() + " " + p2.getName() + " played " +
                p2c.toString() + ".";
        turn += "draw. ";
        p1c = this->p1.pullCard();
        p2c = this->p2.pullCard();
    }
    turn += p1.getName() + " played " + p1c.toString() + " " + p2.getName() + " played " +
            p2c.toString() + ".";
    p1war.push_back(p1c);
    p2war.push_back(p2c);

    // cout << turn << endl;
    string winnerName = "";
    if (p1c.getNum() > p2c.getNum())
    {
        if (p2c.getNum() == 1 && p1c.getNum() != 2) // player 2 won
            winnerName = p2.getName();
        else
        {
            p1_turns_won++;
            winnerName = p1.getName();
        }
    }
    else
    {
        if (p1c.getNum() == 1 && p2c.getNum() != 2) // player 1 won
        {
            p1_turns_won++;
            winnerName = p1.getName();
        }
        else
            winnerName = p2.getName();
    }
    if (winnerName == p1.getName())
    {
        p1.setCardsTaken(p1.cardesTaken() + (int)p1war.size() + (int)p2war.size());
        turn += " " + p1.getName() + " wins.";
    }
    else
    {
        p2.setCardsTaken(p2.cardesTaken() + (int)p1war.size() + (int)p2war.size());
        turn += " " + p2.getName() + " wins.";
    }

    game_log.push_back(turn + "\n");
}
void Game::printLastTurn()
{
    if (!game_log.empty())
        cout << game_log.back() << endl;
    else
        cout << "A turn hasn't been made yet!" << endl;
}
void Game::printWiner()
{
    int p1_cards = this->p1.cardesTaken();
    int p2_cards = this->p2.cardesTaken();
    if (p1_cards + p2_cards != 52)
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
        p1.setPlaying(false);
        p1.setCardsTaken(0);
        p2.setPlaying(false);
        p2.setCardsTaken(0);
    }
}
void Game::printLog()
{
    for (auto i : game_log)
    {
        cout << i;
    }
}
void Game::printStats() // for each player prints basic statistics: win rate, cards won
{
    cout << p1.getName() << " has a win rate of: " << p1_turns_won / num_of_turns << ", and won " << p1.cardesTaken() << " cards" << endl;
    cout << p2.getName() << " has a win rate of: " << 1 - (p1_turns_won / num_of_turns) << ", and won " << p2.cardesTaken() << " cards" << endl;
}