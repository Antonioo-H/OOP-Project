#include <iostream>
#include <ctime>
#include <windows.h>
#include <rlutil.h>
using namespace std;

class Snake
{
    int x;
    int y;
public:
    Snake(int a = 5, int b = 5){x = a; y = b;} /// snake position by default
    ~Snake()= default;
    void set_snakeX(int a) {x = a;}
    void set_snakeY(int b) {y = b;}
    int get_snakeX() const {return x;}
    int get_snakeY() const {return y;}
    Snake(const Snake& snake)
    {
        this->x = snake.x;
        this->y = snake.y;
    }
    Snake& operator= (const Snake& a)
    {
        if(this != &a)
        {
            this->x = a.x;
            this->y = a.y;
        }
        return *this;
    }
};

class Tail
{
    Snake v[200];   /// TODO: vector<Snake> v
    int ntail = 0;
public:
    Tail() = default;
    ~Tail()= default;
    void add(int i, const Snake& snake) {v[i] = snake;}
    void set_ntail(int a = 1) {ntail += a;}
    int get_ntail() const {return ntail;}
    Snake get_element(int i) {return v[i];}
};

class Food
{
    int x;
    int y;
public:
    Food() = default;
    ~Food()= default;
    void set_FoodX(int a) {x = a;}
    void set_FoodY(int b) {y = b;}
    int get_FoodX() const {return x;}
    int get_FoodY() const {return y;}
};

class Game
{
    const int height = 15;
    const int width = 20;
public:
    enum Directions {Stop, Left, Right, Up, Down};
    int score = 0;
    bool GameOver;
    Directions dir = Stop;

    void Setup(Food&);
    void Draw(Snake&, Food&, Tail&);
    void Input();
    void Logic(Snake&, Food&, Tail&);
};

void Game::Setup(Food& apple)
{
    GameOver = false;
    srand(time(nullptr));
    apple.set_FoodX(rand() % (width - 2));
    apple.set_FoodY(rand() % (height - 2));
}

void Game::Draw(Snake& snake, Food& apple, Tail& tail)
{
    system("cls");
    int i,j,k,n;
    bool ok;
    for(i = -1; i <= width-2; i++)
        cout << '#';
    cout << '\n';

    for(j = 0; j <= height-1; j++)
    {
        for(i = -1; i <= width-2; i++)
            if(i == -1 || i == width-2)
                cout << '#';
            else
            if(i == snake.get_snakeX() && j == snake.get_snakeY())
                cout << "O";
            else
            if(i == apple.get_FoodX() && j == apple.get_FoodY())
                cout << "*";
            else
            {
                ok = false;
                n = tail.get_ntail();
                for(k = 1; k <= n; k++)
                    if((tail.get_element(k)).get_snakeX() == i && (tail.get_element(k)).get_snakeY() == j)
                    {
                        ok = true;
                        break;
                    }
                if(!ok)
                    cout << ' ';
                else
                    cout << 'o';

            }
        cout << '\n';
    }

    for(i = -1; i <= width-2; i++)
        cout << '#';
    cout << "\nScor: " << score;
}

void Game::Input()
{
    if(kbhit())
    {
        switch (getch())
        {
            case 'a':
                dir = Left;
                break;

            case 'd':
                dir = Right;
                break;

            case 's':
                dir = Down;
                break;

            case 'w':
                dir = Up;
                break;
        }
    }
}

void Game::Logic(Snake& snake, Food& apple, Tail& tail)
{
    Snake prev1(snake);

    switch (dir)
    {
        case Left:
            snake.set_snakeX(snake.get_snakeX()-1);
            break;

        case Right:
            snake.set_snakeX(snake.get_snakeX()+1);
            break;

        case Up:
            snake.set_snakeY(snake.get_snakeY()-1);
            break;

        case Down:
            snake.set_snakeY(snake.get_snakeY()+1);
            break;

        default:
            break;
    }

    int i,n = tail.get_ntail();
    Snake prev2;

    for(i = 1; i <= n; i++)
    {
        prev2 = tail.get_element(i);
        tail.add(i,prev1);
        prev1 = prev2;
    }

    if(snake.get_snakeX() == apple.get_FoodX() && snake.get_snakeY() == apple.get_FoodY())
    {
        score++;
        tail.set_ntail();
        apple.set_FoodX(rand() % (width - 2));
        apple.set_FoodY(rand() % (height - 2));
    }

    if(snake.get_snakeX() == -1)        GameOver = true;
    if(snake.get_snakeX() == width-2)   GameOver = true;
    if(snake.get_snakeY() == -1)        GameOver = true;
    if(snake.get_snakeY() == height-2)  GameOver = true;

    n = tail.get_ntail();
    for(i = 1; i <= n; i++)
        if(snake.get_snakeX() == (tail.get_element(i)).get_snakeX() && snake.get_snakeY() == (tail.get_element(i)).get_snakeY())
        {
            GameOver = true;
            break;
        } /// bug pentru pozitia marului in originea sistemului de coordonate carteziene!
}

int main()
{
    rlutil::setColor(1);

    Snake snake;
    Tail tail;
    Food apple;
    Game game;

    game.Setup(apple);
    while(!game.GameOver)
    {
        game.Input();
        game.Logic(snake,apple,tail);
        game.Draw(snake,apple,tail);
        Sleep(50);
    }

    return 0;
}