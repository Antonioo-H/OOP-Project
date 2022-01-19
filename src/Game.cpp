#include "../headers/Game.h"

Game* Game::instance = nullptr;

Game *Game::get_instance() {
    if(instance == nullptr)
    {
        instance = new Game();
    }
    return instance;
}

Game::~Game()
{
    for(auto& it : food)
        delete it;
    food.clear();
}

void Game::Setup()
{
    GameOver = false;
    score = 0;
    dir = Stop;
    food.push_back(new Apple());
    food.push_back(new Poisoned_Apple());
    current = &food[0];
    int x, y;
    do {
        x = rand() % (board.get_height() - 1);
    } while(x == 0);

    do {
        y = rand() % (board.get_width() - 1);
    } while(y == 0);

    (*current)->set_FoodX(x);
    (*current)->set_FoodY(y);
}

void Game::Draw()
{
    rlutil::cls();
    board.clear_board();
    //initializez variabilele width si height pt a nu apela de multe ori getterii
    int width = board.get_width();
    int height = board.get_height();
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
    if((*current)->effect(*this, tail, board, snake))
    {
        int minim = min(board.get_height(), board.get_width());
        int p = 0;
        // cat timp sarpele are o anumita lungime, pot genera si mere otravite
        if(snake.get_ntail() <= ceil(minim/2)-3)
        {
            int j = rand() % 2;
            for(int i = 1; i <= j; i++)
                p++;
        }
        current = &food[p];
        int a = 0, b = 0;
        (*current)->new_position(board, snake, a, b);
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
    if(x == 0 || x == board.get_height()-1)
    {
        GameOver = true;
        throw eroare_coliziune();
    }
    if(y == 0 || y == board.get_width()-1)
    {
        GameOver = true;
        throw eroare_coliziune();
    }

    // cap coliziune cu corpul
    int n = snake.get_ntail();
    for(int i = 1; i <= n; i++)
        if(x == snake.get_element(i).get_cellX() && y == snake.get_element(i).get_cellY())
        {
            GameOver = true;
            throw eroare_coliziune();
        }
}

void Game::Logic()
{
    Move();
    Collision();
}

void Game::Play()
{
    try{
        Input();
        Logic();
        Draw();
    }
    catch(exception &err) {cout << err.what() << '\n';}
}
