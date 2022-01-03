#include "../libraries/rlutil.h"
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

int Board::get_height() {return height;}

int Board::get_width() {return width;}

void Board::set_height(int x) {height = x;}

void Board::set_width(int y) {width = y;}

void Board::set_point(int x, int y, char val) {board[x][y] = val;}

char Board::get_point(int x, int y) const {return board[x][y];}

ostream& operator<< (ostream& out, const Board& ob)
{
    for(int i = 0; i < Board::height; i++)
    {
        for(int j = 0; j < Board::width; j++)
            if(ob.get_point(i,j) == 'O')
            {
                rlutil::setColor(4); // RED
                out << ob.get_point(i,j) << ' ';
                rlutil::setColor(1); // BLUE
            }
            else
                if(ob.get_point(i,j) == 'o')
                {
                    rlutil::setColor(2); // GREEN
                    out << ob.get_point(i,j) << ' ';
                    rlutil::setColor(1);
                }
                else
                    if(ob.get_point(i,j) == '*')
                    {
                        rlutil::setColor(6); // YELLOW
                        out << ob.get_point(i,j) << ' ';
                        rlutil::setColor(1);
                    }
                    else
                        out << ob.get_point(i,j) << ' ';
        cout << '\n';
    }
    return out;
}

void Board::clear_board()
{
    for(int i = 0; i < Board::height; i++)
        for(int j = 0; j < Board::width; j++)
            this->set_point(i, j, ' ');
}