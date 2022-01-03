#ifndef OOP_PROJECT_APPLE_H
#define OOP_PROJECT_APPLE_H
#include "Food.h"

class Apple : public Food
{
public:
    Apple() = default;
    ~Apple() override = default;
    bool effect(Game&, Cell&, Board&, Snake&) override;
    friend ostream& operator<< (ostream& out, const Apple& ob);
};

#endif
