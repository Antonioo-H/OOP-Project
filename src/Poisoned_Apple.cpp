#include "../headers/Poisoned_Apple.h"
#include "../headers/Game.h"

bool Poisoned_Apple::effect(Game &game, Cell &tail, Board &board, Snake &snake)
{
    if(snake.get_head().get_cellX() == this->get_FoodX() && snake.get_head().get_cellY() == this->get_FoodY())
    {
        Board::set_height(Board::get_height()-1);
        Board::set_width(Board::get_width()-1);
        return true;
    }
    return false;
}

ostream& operator<< (ostream& out, const Poisoned_Apple& ob)
{
    out << ob.get_FoodX() << '\n';
    out << ob.get_FoodY() << '\n';
    return out;
}