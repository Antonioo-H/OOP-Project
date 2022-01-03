#include "../headers/Game.h"

Game::Game() {Setup();} // Setup-ul jocului se face implicit la instantierea unui obiect

Game::~Game()
{
    for(auto& it : food)
        delete it;
}

void Game::Setup()
{
    GameOver = false;
    score = 0;
    dir = Stop;
    food.push_back(new Apple());
    food.push_back(new Poisoned_Apple());
    current = food.data();
    int x, y;
    do {
        x = rand() % (Board::get_height() - 1);
    } while(x == 0);

    do {
        y = rand() % (Board::get_width() - 1);
    } while(y == 0);
    (*current)->set_FoodX(x);
    (*current)->set_FoodY(y);
}

void Game::Draw()
{
    rlutil::cls();
    board.clear_board();
    //initializez variabilele width si height pt a nu apela de multe ori getterii
    int width = Board::get_width();
    int height = Board::get_height();
    int n = snake.get_ntail();

    // limite tabla
    for(int i = 0; i < width; i++)
    {
        board.set_point(0, i, '#');
        board.set_point(height-1, i, '#');
    }

    for(int i = 1; i < height-1; i++)
    {
        board.set_point(i, 0, '#');
        board.set_point(i, width-1, '#');
    }

    // cap
    board.set_point(snake.get_head().get_cellX(), snake.get_head().get_cellY(), 'O');

    // coada
    // s-a inceput iteratia de la 1, deoarece in vector, pozitia 0 este ocupata de capul sarpelui (afisat mai sus)
    for(int i = 1; i <= n; i++)
        board.set_point(snake.get_element(i).get_cellX(), snake.get_element(i).get_cellY(), 'o');

    // mar
    board.set_point((*current)->get_FoodX(), (*current)->get_FoodY(), '*');

    cout << board;
    cout << "\nScor: " << score << '\n';
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

void Game::gotFood(Cell& tail)
{
    // momentul cand pozitia marului este aceeasi cu cea a capului sarpelui
    if((*current)->effect(*this, tail, board, snake) == 1)
    {
        int minim = min(Board::get_height(), Board::get_width());
        current = food.data();
        // cat timp sarpele are o anumita lungime, pot genera si mere otravite (tip_mar = 2)
        if(snake.get_ntail() <= ceil(minim/2)-3)
        {
            int j = rand() % 2;
            for(int i = 1; i <= j; i++)
                current++;
        }
        int a = 0, b = 0, type;
        if(typeid(**current) == typeid(Apple)) type = 1;
        else type = 2;
        (*current)->new_position(board, snake, a, b, type);
        (*current)->set_FoodX(a);
        (*current)->set_FoodY(b);
    }
}

void Game::Move()
{
    Cell head = snake.get_head();
    Cell tail = snake.get_lastElement();

    int n = snake.get_ntail();
    for(int i = n; i >= 1; i--) snake.assign(i,snake.get_element(i-1)); // fac mutari in vector

    switch (dir) // setez noile coordonate pt elementul principal (capul)
    {
        case Left:
            head.set_cellY(head.get_cellY()-1);
            break;

        case Right:
            head.set_cellY(head.get_cellY()+1);
            break;

        case Up:
            head.set_cellX(head.get_cellX()-1);
            break;

        case Down:
            head.set_cellX(head.get_cellX()+1);
            break;

        default:
            break;
    }
    snake.assign(0,head);
    gotFood(tail);
}

void Game::Collision()
{
    int x = snake.get_head().get_cellX();
    int y = snake.get_head().get_cellY();

    // cap coliziune cu tabla
    if(x == 0 || x == Board::get_height()-1)  GameOver = true;
    if(y == 0 || y == Board::get_width()-1)   GameOver = true;

    // cap coliziune cu corpul
    int n = snake.get_ntail();
    for(int i = 1; i <= n; i++)
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
