#include "../headers/Snake.h"

Snake::Snake() {v.emplace_back(5,5);} /// snake position by default

void Snake::assign(int i, const Cell& snake) {v.at(i) = snake;}

void Snake::resize(const Cell& ob) {v.resize(ntail+1,ob);} // aloc memorie pentru inca un element ce va fi pus in container

void Snake::set_ntail(int a) {ntail += a;}

int Snake::get_ntail() const {return ntail;}

Cell Snake::get_head() const {return v.front();}

Cell Snake::get_lastElement() const {return v.back();}

Cell Snake::get_element(int i) const {return v.at(i);}

ostream& operator<< (ostream& out, const Snake& ob)
{
    int i, n = ob.get_ntail();
    for(i = 0; i <= n; i++)
        out << "Coordonate element " << i << ':' << '(' << ob.get_element(i).get_cellX() << ", " << ob.get_element(i).get_cellY() << ')' << '\n';

    return out;
}