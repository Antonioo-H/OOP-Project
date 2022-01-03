#ifndef OOP_PROJECT_POISONED_APPLE_H
#define OOP_PROJECT_POISONED_APPLE_H
#include "Food.h"

class Poisoned_Apple : public Food
{
public:
    Poisoned_Apple() = default;
    ~Poisoned_Apple() override = default;
    bool effect(Game&, Cell&, Board&, Snake&) override;
    friend ostream& operator<< (ostream& out, const Poisoned_Apple& ob);
};

#endif
