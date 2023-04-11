#ifndef GAME_H
#define GAME_H

#include "player.hpp"
#include <vector>
namespace ariel
{
    class Game
    {
        Player &pl1;
        Player &pl2;
        vector<string> game_log;
        int p1_turns_won;
        int num_of_turns;
        int num_of_draws;

    public:
        Game(Player &player1, Player &player2);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
};

#endif