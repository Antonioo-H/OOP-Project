#ifndef OOP_PROJECT_FOOD_H
#define OOP_PROJECT_FOOD_H
#include <iostream>
#include <cmath>
#include "Snake.h"
#include "Board.h"

using namespace std;

class Game;

class Food
{
protected:
    int x{};
    int y{};
public:
    Food() = default;
    Food(int _x, int _y);
    virtual ~Food() = default;
    void set_FoodX(int);
    void set_FoodY(int);
    int get_FoodX() const;
    int get_FoodY() const;
    virtual void new_position(Board &board, Snake &snake, int &a, int &b) = 0;
    virtual bool effect(Game &game, Cell &tail, Board &board, Snake &snake) = 0;
};

#endif
