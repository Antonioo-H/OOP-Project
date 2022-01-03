#ifndef OOP_PROJECT_BOARD_H
#define OOP_PROJECT_BOARD_H
#include <iostream>
#include <vector>
using namespace std;

class Board
{
    static int height;
    static int width;
    vector<vector<char>> board;
public:
    Board();
    ~Board() = default;
    static int get_height();
    static int get_width();
    static void set_height(int x);
    static void set_width(int y);
    void set_point(int x, int y, char val);
    char get_point(int x, int y) const;
    friend ostream& operator<< (ostream&, const Board&);
    void clear_board();
};

#endif
