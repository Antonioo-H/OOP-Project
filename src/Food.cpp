#include "../headers/Food.h"

void Food::set_FoodX(int a) {x = a;}

void Food::set_FoodY(int b) {y = b;}

int Food::get_FoodX() const {return x;}

int Food::get_FoodY() const {return y;}

ostream& operator<< (ostream& out, const Food& ob)
{
    out << ob.get_FoodX() << '\n';
    out << ob.get_FoodY() << '\n';
    return out;
}