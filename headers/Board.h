#ifndef OOP_PROJECT_BOARD_H
#define OOP_PROJECT_BOARD_H
#include <iostream>
#include <vector>
using namespace std;

class Board
{
protected:
    static int height;
    static int width;
    vector<vector<char>> board;
public:
    Board();
    ~Board() = default;
    static int get_height() {return height;}
    static int get_width() {return width;}
    void set_point(int, int, char);
    char get_point(int x, int y) const;
    friend ostream& operator<< (ostream&, const Board&);
};

#endif
