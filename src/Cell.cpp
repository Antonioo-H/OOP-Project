#include "../headers/Cell.h"

Cell::Cell(const Cell& cell)
{
    this->x = cell.x;
    this->y = cell.y;
}

Cell& Cell::operator= (const Cell& a)
{
    if(this != &a)
    {
        this->x = a.x;
        this->y = a.y;
    }
    return *this;
}

ostream& operator<< (ostream& out, const Cell& ob)
{
    out << ob.x << '\n';
    out << ob.y << '\n';
    return out;
}