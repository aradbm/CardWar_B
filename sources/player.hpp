#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "card.hpp"
using namespace std;
namespace ariel
{
    class Player
    {
        string name;
        vector<Card> player_stack;
        int cardsTaken;
        bool isPlaying;

    public:
        Player(string name);
        string getName();
        int stacksize();
        int cardesTaken();
        void setCardsTaken(int num);
        bool getIsPlaying();
        void setPlaying(bool bool1);
        void addCard(Card card_to_add);
        Card pullCard();
    };
};
#endif