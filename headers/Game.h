#ifndef OOP_PROJECT_GAME_H
#define OOP_PROJECT_GAME_H
#include <ctime>
#include "../libraries/rlutil.h"
#include "Apple.h"
#include "Poisoned_Apple.h"
#include "Eroare.h"

class Game
{
    Board board;
    vector<Food*> food;
    Food** current;
    Snake snake;
    int score;
    bool GameOver;
    enum Directions {Stop, Left, Right, Up, Down};
    Directions dir;


    static Game* instance;
    void Setup();
    Game() {Setup();}
    void Input();
    void gotFood(Cell&);
    void Move();
    void Collision();
    void Logic();
    void Draw();
public:

    ~Game();
    void set_score(int x) {score = x;}
    int get_score() const {return score;}
    void Play();
    bool isOver() const {return GameOver;}
    static Game* get_instance();
};

#endif