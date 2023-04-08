#ifndef CARD_H
#define CARD_H
#include <iostream>
using namespace std;

namespace ariel
{
    class Card
    {
        int num;
        int shape; // 1 to 4, representing each shape in a cards deck.

    public:
        Card(int num = 1, int shape = 1);
        int getNum();
        int getShape();
        string toString();
    };
};
#endif