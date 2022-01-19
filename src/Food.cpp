#include "../headers/Food.h"
#include "../headers/Game.h"

Food::Food(int _x, int _y) : x(_x), y(_y){}

void Food::set_FoodX(int a) {x = a;}

void Food::set_FoodY(int b) {y = b;}

int Food::get_FoodX() const {return x;}

int Food::get_FoodY() const {return y;}