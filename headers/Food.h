#ifndef OOP_PROJECT_FOOD_H
#define OOP_PROJECT_FOOD_H
#include <iostream>
using namespace std;

class Food
{
protected:
    int x;
    int y;
public:
    Food() = default;
    ~Food()= default;
    void set_FoodX(int);
    void set_FoodY(int);
    int get_FoodX() const;
    int get_FoodY() const;
    friend ostream& operator<< (ostream& out, const Food& ob);
};

#endif
