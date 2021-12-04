#include <rlutil.h>
#include "../headers/Board.h"

int Board::height = 15;
int Board::width = 20;

Board::Board()
{
    board.reserve(height);
    for(int i = 0; i < height; i++)
    {
        vector<char> v(width, ' ');
        board.push_back(v);
    }
}

void Board::set_point(int x, int y, char val) {board[x][y] = val;}

char Board::get_point(int x, int y) const {return board[x][y];}

ostream& operator<< (ostream& out, const Board& ob)
{
    int i, j;
    for(i = 0; i < Board::height; i++)
    {
        for(j = 0; j < Board::width; j++)
            if(ob.get_point(i,j) == 'O')
            {
                rlutil::setColor(4);
                out << ob.get_point(i,j) << ' ';
                rlutil::setColor(1);
            }
            else
                if(ob.get_point(i,j) == 'o')
                {
                    rlutil::setColor(2);
                    out << ob.get_point(i,j) << ' ';
                    rlutil::setColor(1);
                }
                else
                    if(ob.get_point(i,j) == '*')
                    {
                        rlutil::setColor(6);
                        out << ob.get_point(i,j) << ' ';
                        rlutil::setColor(1);
                    }
                    else
                        out << ob.get_point(i,j) << ' ';
        cout << '\n';
    }
    return out;
}