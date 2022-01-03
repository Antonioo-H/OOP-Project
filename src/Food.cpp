#include "../headers/Food.h"
#include "../headers/Game.h"

Food::Food(int _x, int _y) : x(_x), y(_y){}

void Food::set_FoodX(int a) {x = a;}

void Food::set_FoodY(int b) {y = b;}

int Food::get_FoodX() const {return x;}

int Food::get_FoodY() const {return y;}

void Food::new_position(Board &board, Snake &snake, int &x1, int &y1, int tip_mar)
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
        if(tip_mar == 1)
        {
            do {
                x1 = rand() % (Board::get_height() - 1);
            } while(x1 == 0);

            do {
                y1 = rand() % (Board::get_width() - 1);
            } while(y1 == 0);
        }
        else
        {
            int minim = min(Board::get_height(), Board::get_width());
            for(int j = 0; j <= ceil(minim/2)-3; j++)
            {
                if(n == j)
                {
                    do {
                        x1 = rand() % (Board::get_height() - (j+2));
                    } while(x1 <= j+1);

                    do {
                        y1 = rand() % (Board::get_width() - (j+2));
                    } while(y1 <= j+1);

                    break;
                }
            }
            /*
             * Limitarile 'ciudate' de mai sus (tip_mar = 2) sunt o generalizare a modului in care programul
             * genereaza pozitia unui mar otravit (mai jos, in comentarii este structura de la care am plecat
             * cu generaliarea pentru limitele tablei de joc oferite). Intucat efectul unui mar otravit micsoreaza
             * tabla de joc am vrut sa evit suprapunerea sarpelui cu tabla (sau eventuale functii de mutare a sarpelui).
             * Asadar, m-am gandit la generarea marului in anumite zone ale tablei, in functie de lungimea sarpelui
             * a.i. in orice pozitie s-ar afla sarpele cand mananca marul, programul sa nu se afle in situatia
             * de suprapunere a sarpelui cu tabla de joc micsorata.
             */

            // Exemplul de la care a plecat generalizarea:
//            switch(n)
//            {
//                case 1:
//                {
//                    do {
//                        x1 = rand() % (Board::get_height() - 3);
//                    } while(x1 == 0 || x1 == 1 || x1 == 2);
//
//                    do {
//                        y1 = rand() % (Board::get_width() - 3);
//                    } while(y1 == 0 || y1 == 1 || y1 == 2);
//
//                    break;
//                }
//                case 2:
//                {
//                    do {
//                        x1 = rand() % (Board::get_height() - 4);
//                    } while(x1 == 0 || x1 == 1 || x1 == 2 || x1 == 3);
//
//                    do {
//                        y1 = rand() % (Board::get_width() - 4);
//                    } while(y1 == 0 || y1 == 1 || y1 == 2 || y1 == 3);
//
//                    break;
//                }
//                case 3:
//                {
//                    do {
//                        x1 = rand() % (Board::get_height() - 5);
//                    } while(x1 == 0 || x1 == 1 || x1 == 2 || x1 == 3 || x1 == 4);
//
//                    do {
//                        y1 = rand() % (Board::get_width() - 5);
//                    } while(y1 == 0 || y1 == 1 || y1 == 2 || y1 == 3 || y1 == 4);
//
//                    break;
//                }
//                case 4:
//                {
//                    do {
//                        x1 = rand() % (Board::get_height() - 6);
//                    } while(x1 == 0 || x1 == 1 || x1 == 2 || x1 == 3 || x1 == 4 || x1 == 5);
//
//                    do {
//                        y1 = rand() % (Board::get_width() - 6);
//                    } while(y1 == 0 || y1 == 1 || y1 == 2 || y1 == 3 || y1 == 4 || y1 == 5);
//
//                    break;
//                }
//                case 5:
//                {
//                    do {
//                        x1 = rand() % (Board::get_height() - 7);
//                    } while(x1 == 0 || x1 == 1 || x1 == 2 || x1 == 3 || x1 == 4 || x1 == 5 || x1 == 6);
//
//                    do {
//                        y1 = rand() % (Board::get_width() - 7);
//                    } while(y1 == 0 || y1 == 1 || y1 == 2 || y1 == 3 || y1 == 4 || y1 == 5 || y1 == 6);
//
//                    break;
//                }
//            }
        }

        for(int i = 0; i <= n; i++) // ma asigur ca marul nu va fi generat pe o pozitie ocupata de sarpe
            if(x1 == snake.get_element(i).get_cellX() && y1 == snake.get_element(i).get_cellY())
            {
                ok = 1;
                break;
            }
    }
}