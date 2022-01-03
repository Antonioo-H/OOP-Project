#ifndef OOP_PROJECT_CELL_H
#define OOP_PROJECT_CELL_H
#include <iostream>
using namespace std;

class Cell
{
    int x;
    int y;
public:
    Cell() = default;
    Cell(int x, int y);
    ~Cell() = default;
    void set_cellX(int a);
    void set_cellY(int b);
    int get_cellX() const;
    int get_cellY() const;
    Cell(const Cell&);
    Cell& operator= (const Cell&);
    friend ostream& operator<< (ostream&, const Cell&);
};

#endif
