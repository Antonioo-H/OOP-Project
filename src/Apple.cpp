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

void Apple::new_position(Board &board, Snake &snake, int &x1, int &y1)
{
    /*
     * Tipuri de mere:
     * 1 - Mar normal
     * 2 - Mar otravit
     */
    // Se face aceasta distinctie, intrucat efectul marului otravit este sa micsoreze spatiul de joc
    /// In acest caz, va trebui sa evit generarea pozitiei unui mar peste limitele tablei de joc
    /// (adica, sa nu se suprapuna cu conturul tablei de joc), dar si peste corpul sarpelui

    int n = snake.get_ntail(), ok = 1;
    // n - retine numarul de celule din coada (la inceputul programului n = 0 - exista doar capul sarpelui)
    while(ok == 1)
    {
        ok = 0;

        do {
            x1 = rand() % (board.get_height() - 1);
        } while(x1 == 0);

        do {
            y1 = rand() % (board.get_width() - 1);
        } while(y1 == 0);

        for(int i = 0; i <= n; i++) // ma asigur ca marul nu va fi generat pe o pozitie ocupata de sarpe
            if(x1 == snake.get_element(i).get_cellX() && y1 == snake.get_element(i).get_cellY())
            {
                ok = 1;
                break;
            }
    }
}
