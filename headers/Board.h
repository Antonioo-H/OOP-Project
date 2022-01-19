#ifndef OOP_PROJECT_BOARD_H
#define OOP_PROJECT_BOARD_H
#include <iostream>
#include <vector>
using namespace std;

class Board
{
    int height = 15;
    int width = 20;
    vector<vector<char>> board;
public:
    Board();
    ~Board() = default;
    int get_height() const;
    int get_width() const;
    void set_height(int x);
    void set_width(int y);
    void set_point(int x, int y, char val);
    char get_point(int x, int y) const;
    friend ostream& operator<< (ostream&, const Board&);
    void clear_board();
};

#endif
