#include <iostream>
#include <ctime>
#include <rlutil.h>
#include <chrono>
#include <thread>
#include <vector>
#include <array>

using namespace std;

class Cell
{
    int x;
    int y;
public:
    Cell(){};
    Cell(int x, int y) : x(x), y(y) {}
    ~Cell() = default;
    void set_cellX(int a) {x = a;}
    void set_cellY(int b) {y = b;}
    int get_cellX() const {return x;}
    int get_cellY() const {return y;}
    Cell(const Cell& cell)
    {
        this->x = cell.x;
        this->y = cell.y;
    }
    Cell& operator= (const Cell& a)
    {
        if(this != &a)
        {
            this->x = a.x;
            this->y = a.y;
        }
        return *this;
    }
    friend ostream& operator<< (ostream& out, const Cell& ob);
};

ostream& operator<< (ostream& out, const Cell& ob)
{
    out << ob.x << '\n';
    out << ob.y << '\n';
    return out;
}

class Snake
{
    vector<Cell> v;
    int ntail = 0;
public:
    Snake() {v.emplace_back(5,5);} /// snake position by default
    ~Snake()= default;
    void assign(int i, const Cell& snake) {v.at(i) = snake;}
    void resize(const Cell& ob) {v.resize(ntail+1,ob);}  // aloc memorie pentru inca un element ce va fi pus in container
    void set_ntail(int a = 1) {ntail += a;}
    int get_ntail() const {return ntail;}
    Cell get_head() const {return v.front();}
    Cell get_lastElement() const {return v.back();}
    Cell get_element(int i) const {return v.at(i);}
    // desi, get_head() si get_lastElement() fac acelasi lucru ca get_element, le-am implementat pentru usurinta apelarii cand am nevoie de
    // coordonatele acestor 2 elemente particulare
    friend ostream& operator<< (ostream& out, const Snake& ob);
};

ostream& operator<< (ostream& out, const Snake& ob)
{
    int i, n = ob.get_ntail();
    for(i = 0; i <= n; i++)
        out << "Coordonate element " << i << ':' << '(' << ob.get_element(i).get_cellX() << ", " << ob.get_element(i).get_cellY() << ')' << '\n';

    return out;
}

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
    friend ostream& operator<< (ostream& out, const Food& ob);
};

ostream& operator<< (ostream& out, const Food& ob)
{
    out << ob.get_FoodX() << '\n';
    out << ob.get_FoodY() << '\n';
    return out;
}

class Board
{
    const int height = 15;
    const int width = 20;
    array<array<char, 20>, 15>board; // tabla care retine viitoarele obstacole (cred Tema 2)
public:
    Board()
    {
        for(int i = 0; i < height; i++)
            board[i].fill(' ');
    }
    int get_height() const {return height;}
    int get_width()  const {return width;}
    void set_point(int x, int y, char val) {board[x][y] = val;}
    char get_point(int x, int y) const {return board[x][y];}
    friend ostream& operator<< (ostream&, const Board&);
};

ostream& operator<< (ostream& out, const Board& ob)
{
    int i, j;
    for(i = 0; i < ob.height; i++)
    {
        for(j = 0; j < ob.width; j++)
            out << ob.get_point(i,j) << ' ';
        cout << '\n';
    }
    return out;
}

class Game
{
    Board board;
    Food apple;
    Snake snake;
    int score;
    bool GameOver;
    enum Directions {Stop, Left, Right, Up, Down};
    Directions dir;

    void Setup()
    {
        GameOver = false;
        score = 0;
        dir = Stop;
        srand(time(nullptr));
        apple.set_FoodX(rand() % (board.get_width() - 2));
        apple.set_FoodY(rand() % (board.get_height() - 2));
    }

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
};

void Game::Draw()
{
    rlutil::cls();
    int i,j,k;
    bool ok;
    //initializez variabilele width si height pt a nu apela de multe ori getterii
    int width = board.get_width();
    int height = board.get_height();
    int n = snake.get_ntail();

    for(i = -1; i <= width-2; i++)
        cout << '#';
    cout << '\n';

    for(j = 0; j <= height-3; j++)
    {
        for(i = -1; i <= width-2; i++)
            if(i == -1 || i == width-2)
                cout << '#';
            else
                if(i == snake.get_head().get_cellX() && j == snake.get_head().get_cellY())
                {
                    rlutil::setColor(4);
                    cout << "O";
                    rlutil::setColor(1);
                }

                else
                    if(i == apple.get_FoodX() && j == apple.get_FoodY())
                    {
                        rlutil::setColor(6);
                        cout << "*";
                        rlutil::setColor(1);
                    }
                    else
                    {
                        ok = false;
                        for(k = 1; k <= n; k++)
                            if((snake.get_element(k)).get_cellX() == i && (snake.get_element(k)).get_cellY() == j)
                            {
                                ok = true;
                                break;
                            }
                        if(!ok)
                            cout << ' ';
                        else
                        {
                            rlutil::setColor(2);
                            cout << 'o';
                            rlutil::setColor(1);
                        }
                    }
        cout << '\n';
    }

    for(i = -1; i <= width-2; i++)
        cout << '#';
    rlutil::setColor(6);
    cout << "\nScor: " << score;
    rlutil::setColor(1);
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

void Game::gotFood(const Cell& tail)
{
    if(snake.get_head().get_cellX() == apple.get_FoodX() && snake.get_head().get_cellY() == apple.get_FoodY())
    {
        score++;
        snake.set_ntail();
        snake.resize(tail); // aloc spatiu pentru noul element si il initializez
        int x = rand() % (board.get_width() - 2);
        int y = rand() % (board.get_height() - 2);
        int n = snake.get_ntail(), ok = 1, i;
        while(ok == 1) // ma asigur ca marul nu va fi generat pe o pozitie ocupata de sarpe
        {
            ok = 0;
            for(i = 0; i <= n; i++)
                if(x == snake.get_element(i).get_cellX() && y == snake.get_element(i).get_cellY())
                {
                    ok = 1;
                    break;
                }
            if(ok == 1)
            {
                x = rand() % (board.get_width() - 2);
                y = rand() % (board.get_height() - 2);
            }
        }
        apple.set_FoodX(x);
        apple.set_FoodY(y);
    }
}

void Game::Move()
{
    Cell head = snake.get_head();
    Cell tail;
    tail = snake.get_lastElement();

    int i, n = snake.get_ntail();
    for(i = n; i >= 1; i--) snake.assign(i,snake.get_element(i-1)); // fac mutari in vector

    switch (dir) // setez noile coordonate pt elementul principal (capul)
    {
        case Left:
            head.set_cellX(head.get_cellX()-1);
            snake.assign(0,head);
            break;

        case Right:
            head.set_cellX(head.get_cellX()+1);
            snake.assign(0,head);
            break;

        case Up:
            head.set_cellY(head.get_cellY()-1);
            snake.assign(0,head);
            break;

        case Down:
            head.set_cellY(head.get_cellY()+1);
            snake.assign(0,head);
            break;

        default:
            break;
    }
    gotFood(tail);
}

void Game::Collision()
{
    int x = snake.get_head().get_cellX();
    int y = snake.get_head().get_cellY();

    // coliziune cu peretii
    if(x == -1 || x == board.get_width()-2)   GameOver = true;
    if(y == -1 || y == board.get_height()-2)  GameOver = true;

    // coliziune cu corpul
    int n = snake.get_ntail(), i;
    for(i = 1; i <= n; i++)
        if(x == snake.get_element(i).get_cellX() && y == snake.get_element(i).get_cellY())
        {
            GameOver = true;
            break;
        }
}

void Game::Logic()
{
    Move();
    Collision();
}

void Game::Play()
{
    Input();
    Logic();
    if(!isOver()) Draw(); // conditie pentru a nu imi desena sarpele (ce se suprapune cu zidul/capul cu corpul) dupa ce s-a lovit
}

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