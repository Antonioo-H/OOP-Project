#ifndef OOP_PROJECT_GAME_H
#define OOP_PROJECT_GAME_H
#include <ctime>
#include <list>
#include "../libraries/rlutil.h"
#include "Apple.h"
#include "Poisoned_Apple.h"
#include "Eroare.h"
#include "Observer.h"

class Game : public Subject
{
    Board board;
    vector<Food*> food;
    Food** current;
    Snake snake;
    int score;
    bool GameOver;
    enum Directions {Stop, Left, Right, Up, Down};
    Directions dir;
    list<Observer*> observerList;

    static Game* instance;
    void Setup();
    Game();
    void Input();
    void gotFood(Cell&);
    void Move();
    void Collision();
    void Logic();
    void Draw();

public:
    ~Game() override;
    void set_score(int x) {score = x; notify();}
    int get_score() const {return score;}
    void Play();
    bool isOver() const {return GameOver;}
    static Game* get_instance();
    void add(Observer* o) override;
    void remove(Observer* o) override;
    void notify() override;
};

class Current_Score : public Observer
{
    int current_score{};
public:
    explicit Current_Score(Game& game){game.add(this);}
    ~Current_Score() override = default;
    void update(int _score) override {current_score = _score;}
    void print_score() const {cout << "\nScorul curent: " << current_score << '\n';}
};

#endif