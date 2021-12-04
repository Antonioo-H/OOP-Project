#ifndef OOP_PROJECT_GAME_H
#define OOP_PROJECT_GAME_H
#include <ctime>
#include <rlutil.h>
#include "Board.h"
#include "Food.h"
#include "Snake.h"

class Game
{
    Board board;
    Food apple;
    Snake snake;
    int score;
    bool GameOver;
    enum Directions {Stop, Left, Right, Up, Down};
    Directions dir;
    void Setup();
public:
    Game() {Setup();} // Setup-ul jocului se face implicit la instantierea unui obiect
    void Input();
    void gotFood(const Cell&);
    void Move();
    void Collision();
    void Logic();
    void Draw();
    void Play();
    bool isOver() const {return GameOver;}
    void override();
};

#endif
