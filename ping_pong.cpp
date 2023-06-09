#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>ṇ

using namespace std;

enum eDir
{
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

class cBall
{
private:
    int x, y;
    int originalX, originalY;
    eDir direction;

public:
    cBall(int posX, int posY)
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
        direction = STOP;
    }
    void changeinDirection(eDir d)
    {
        direction = d;
    }

    void randomDirection()
    {
        direction = (eDir)((rand() % 6) + 1);
    }

    inline int getX()
    {
        return x;
    }
    inline int getY()
    {
        return y;
    }
    inline eDir getdirection()
    {
        return direction;
    }
    void Move()
    {
        switch (direction)
        {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
        }
    }
};

class cPaddle
{
private:
    int x, y;
    int originalX, originalY;

public:
    cPaddle()
    {
        x = y = 0;
    }
    cPaddle(int posX, int posY) : cPaddle()
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    inline void Reset()
    {
        x = originalX;
        y = originalY;
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveup() { y--; }
    inline void movedown() { y++; }
};

class cGameManager
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;

public:
    cGameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }
    ~cGameManager()
    {
        delete ball, player1, player2;
    }
    void Scoreup(cPaddle *player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw()
    {
        system("cls");

        for (int i = 0; i < width + 2; i++)
            cout << "\xB1";
        cout << endl; // upperwall

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                if (j == 0)
                    cout << "\xB1";
                if (ballx == j && bally == i)
                    cout << "0"; // ball
                else if (player1x == j && player1y == i)
                    cout << "\xDB"; // player1
                else if (player1x == j && player1y + 1 == i)
                    cout << "\xDB"; // player1
                else if (player1x == j && player1y + 2 == i)
                    cout << "\xDB"; // player1
                else if (player1x == j && player1y + 3 == i)
                    cout << "\xDB"; // player1
                else if (player2x == j && player2y == i)
                    cout << "\xDB"; // player2
                else if (player2x == j && player2y + 1 == i)
                    cout << "\xDB"; // player2
                else if (player2x == j && player2y + 2 == i)
                    cout << "\xDB"; // player2
                else if (player2x == j && player2y + 3 == i)
                    cout << "\xDB"; // player2
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB1";
            }

            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB1";
        cout << endl; // lowerwall

        cout << "player1  " << score1 << "          "
             << "player2  " << score2 << endl;
    }

    void Input()
    {
        ball->Move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        if (_kbhit())
        {
            char current = _getch();
            if (current == up1)
                if (player1y > 0)
                    player1->moveup();
            if (current == up2)
                if (player2y > 0)
                    player2->moveup();
            if (current == down1)
                if (player1y + 4 < height)
                    player1->movedown();
            if (current == down2)
                if (player2y + 4 < height)
                    player2->movedown();
            if (ball->getdirection() == STOP)
                ball->randomDirection();
            if (current == 'q')
                quit = true;
        }
    }
    void logic()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();
        // left paddle

        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1)
                if (bally == player1y + i)
                    ball->changeinDirection((eDir)((rand() % 3) + 4));

        // right paddle

        for (int i = 0; i < 4; i++)
            if (ballx == player2x - 1)
                if (bally == player2y + i)
                    ball->changeinDirection((eDir)((rand() % 3) + 1));

        // bottomwall

        if (bally == height - 1)
            ball->changeinDirection(ball->getdirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

        // topwall

        if (bally == 0)
            ball->changeinDirection(ball->getdirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

        // right wall
        if (ballx == width - 1)
            Scoreup(player1);

        // leftwall
        if (ballx == 0)
            Scoreup(player2);
    }

    void Run()
    {
        while (!quit)
        {
            Draw();
            Input();
            logic();
        }
    }
};

int main()
{
    cGameManager a(40, 20);
    a.Run();
    return 0;
}
