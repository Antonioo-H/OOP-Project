#include <chrono>
#include "libraries/rlutil.h"
#include <thread>
#include <ctime>
#include "headers/Game.h"

int main()
{
    srand(time(nullptr));
    rlutil::setColor(1); // BLUE
    Game game;
    while(!game.isOver())
    {
        game.Play();
        this_thread::sleep_for(chrono::milliseconds(120));
    }

    return 0;
}