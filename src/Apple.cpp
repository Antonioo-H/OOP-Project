#include "../headers/Apple.h"
#include "../headers/Game.h"

bool Apple::effect(Game &game, Cell &tail, Board &board, Snake &snake)
{
    if(snake.get_head().get_cellX() == this->get_FoodX() && snake.get_head().get_cellY() == this->get_FoodY())
    {
        game.set_score(game.get_score()+1);
        snake.set_ntail();
        snake.resize(tail); // aloc spatiu pentru noul element si il initializez
        return true;
    }
    return false;
}

ostream& operator<< (ostream& out, const Apple& ob)
{
    out << ob.get_FoodX() << '\n';
    out << ob.get_FoodY() << '\n';
    return out;
}
