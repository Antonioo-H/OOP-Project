#include "../headers/Cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {}

void Cell::set_cellX(int a) {x = a;}

void Cell::set_cellY(int b) {y = b;}

int Cell::get_cellX() const {return x;}

int Cell::get_cellY() const {return y;}

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