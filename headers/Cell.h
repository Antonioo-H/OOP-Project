#ifndef OOP_PROJECT_CELL_H
#define OOP_PROJECT_CELL_H
#include <iostream>
using namespace std;

class Cell
{
    int x;
    int y;
public:
    Cell(){};
    Cell(int x, int y) : x(x), y(y) {}
    ~Cell() = default;
    void set_cellX(int a) {x = a;}
    void set_cellY(int b) {y = b;}
    int get_cellX() const {return x;}
    int get_cellY() const {return y;}
    Cell(const Cell&);
    Cell& operator= (const Cell&);
    friend ostream& operator<< (ostream&, const Cell&);
};

#endif
