#ifndef GAME_H
#define GAME_H

#include "player.hpp"
#include <vector>
namespace ariel
{
    class Game
    {
        Player p1;
        Player p2;
        vector<string> game_log;
        int p1_turns_won;
        int num_of_turns;

    public:
        Game(Player player1, Player player2);
        ~Game();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
};

#endif