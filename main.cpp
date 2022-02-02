#include <chrono>
#include "libraries/rlutil.h"
#include <thread>
#include <ctime>
#include "headers/Game.h"

int main()
{
    srand(time(nullptr));
    rlutil::setColor(1); // BLUE
    Game *game = Game::get_instance();
    Current_Score* current_score = new Current_Score(*game);
    while(!game->isOver())
    {
        game->Play();
        current_score->print_score();
        this_thread::sleep_for(chrono::milliseconds(120));
    }
    delete current_score;

    return 0;
}