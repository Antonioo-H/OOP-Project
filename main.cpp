#include <chrono>
#include <rlutil.h>
#include <thread>
#include <vector>
#include "headers/Cell.h"
#include "headers/Snake.h"
#include "headers/Food.h"
#include "headers/Board.h"
#include "headers/Game.h"

int main()
{
    rlutil::setColor(1);
    Game game;
    while(!game.isOver())
    {
        game.Play();
        this_thread::sleep_for(chrono::milliseconds(120));
    }

    return 0;
}