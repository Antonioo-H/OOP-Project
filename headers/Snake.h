#ifndef OOP_PROJECT_SNAKE_H
#define OOP_PROJECT_SNAKE_H
#include <vector>
#include "Cell.h"

class Snake
{
protected:
    vector<Cell> v;
    int ntail = 0;
public:
    Snake(); /// snake position by default
    ~Snake()= default;
    void assign(int, const Cell&);
    void resize(const Cell&);  // aloc memorie pentru inca un element ce va fi pus in container
    void set_ntail(int a = 1);
    int get_ntail() const;
    Cell get_head() const;
    Cell get_lastElement() const;
    Cell get_element(int i) const;
    // desi, get_head() si get_lastElement() fac acelasi lucru ca get_element, le-am implementat pentru usurinta apelarii cand am nevoie de
    // coordonatele acestor 2 elemente particulare
    friend ostream& operator<< (ostream& out, const Snake& ob);

};

#endif
