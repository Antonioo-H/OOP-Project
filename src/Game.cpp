#include "../headers/Game.h"

void Game::override()
{
    int i,j;
    int height = Board::get_height();
    int width = Board::get_width();
    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++)
            board.set_point(i, j, ' ');
}

void Game::Setup()
{
    GameOver = false;
    score = 0;
    dir = Stop;
    srand(time(nullptr));
    int x = rand() % (Board::get_height() - 2);
    if(x == 0) x++;
    int y = rand() % (Board::get_width() - 2);
    if(y == 0) y++;
    apple.set_FoodX(x);
    apple.set_FoodY(y);
}

void Game::Draw()
{
    rlutil::cls();
    override();
    int i;
    //initializez variabilele width si height pt a nu apela de multe ori getterii
    int width = Board::get_width();
    int height = Board::get_height();
    int n = snake.get_ntail();

    // limite tabla
    for(i = 0; i < width; i++)
    {
        board.set_point(0, i, '#');
        board.set_point(height-1, i, '#');
    }

    for(i = 1; i < height-1; i++)
    {
        board.set_point(i, 0, '#');
        board.set_point(i, width-1, '#');
    }

    // cap
    board.set_point(snake.get_head().get_cellX(), snake.get_head().get_cellY(), 'O');

    // coada
    for(i = 1; i <= n; i++)
        board.set_point(snake.get_element(i).get_cellX(), snake.get_element(i).get_cellY(), 'o');

    // mar
    board.set_point(apple.get_FoodX(), apple.get_FoodY(), '*');

    cout << board;
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

void Game::gotFood(const Cell& tail)
{
    if(snake.get_head().get_cellX() == apple.get_FoodX() && snake.get_head().get_cellY() == apple.get_FoodY())
    {
        score++;
        snake.set_ntail();
        snake.resize(tail); // aloc spatiu pentru noul element si il initializez
        int x = rand() % (Board::get_height() - 2);
        if(x == 0) x++;
        int y = rand() % (Board::get_width() - 2);
        if(y == 0) y++;
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
                x = rand() % (Board::get_height() - 2);
                if(x == 0) x++;
                y = rand() % (Board::get_width() - 2);
                if(y == 0) y++;
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
            head.set_cellY(head.get_cellY()-1);
            snake.assign(0,head);
            break;

        case Right:
            head.set_cellY(head.get_cellY()+1);
            snake.assign(0,head);
            break;

        case Up:
            head.set_cellX(head.get_cellX()-1);
            snake.assign(0,head);
            break;

        case Down:
            head.set_cellX(head.get_cellX()+1);
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
    if(x == 0 || x == Board::get_height()-1)  GameOver = true;
    if(y == 0 || y == Board::get_width()-1)   GameOver = true;

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
