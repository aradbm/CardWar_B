#include "card.hpp"
using namespace std;
using namespace ariel;
Card::Card(int num, int shape)
{
    this->num = num;
    this->shape = shape;
}
int Card::getNum()
{
    return this->num;
}
int Card::getShape()
{
    return this->shape;
}
string Card::toString()
{
    string str = "";
    switch (this->num)
    {
    case 1:
        str += "Ace";
        break;
    case 11:
        str += "Jack";
        break;
    case 12:
        str += "Queen";
        break;
    case 13:
        str += "King";
        break;

    default:
        str += to_string(num);
        break;
    }
    switch (shape)
    {
    case 1:
        str += " of Hearts";
        break;
    case 2:
        str += " of Diamonds";
        break;
    case 3:
        str += " of Spades";
        break;
    case 4:
        str += " of Clubs";
        break;
    default:
        break;
    }
    return str;
}