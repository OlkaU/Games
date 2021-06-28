#include "TXlib.h"

struct Ball
    {
    double x, y;
    int radius ;

    COLORREF bodyColor;
    COLORREF contourColor;

    double vx, vy, dt;

    void DrawBall ();
    };

struct Platform
    {
    double x;
    double widthX;

    COLORREF bodycolor;

    void Draw ();
   // void Control ();
    };

//- - - - - - - - - - - - рисование шарика  - - - - - - - - - - - - - - - - - -
void Ball::DrawBall ()
    {
    txSetColor (bodyColor, 2);
    txSetFillColor (contourColor);

    txCircle (x, y, radius);
    }

//- - - - - - - - - - - - рисование платформы - - - - - - - - - - - - - - - - - -
void Platform::Draw ()
    {
    txSetColor     (bodycolor);
    txSetFillColor (bodycolor);
    txRectangle    (x, txGetExtentY() - 100 - 20, x + widthX, txGetExtentY() - 100);

    txSetColor     (TX_WHITE);
    txLine(0, txGetExtentY() - 100, txGetExtentX(), txGetExtentY() - 100);
    }


void DrawField   ();
void MoveBall    (HDC fon);
void PhysicsBall (Ball* ball1, double x, double widthX, int* score, int* life);
void Control     (Platform* platforma);
void TabloScore  (int* score);
void TablLife    (int* life);

//=============================================================================

int main ()
    {
    txCreateWindow (600, 800);

    HDC fon  = txLoadImage ("Img\\fon2.bmp");

    MoveBall (fon);

    return 0;

    }

//=============================================================================

void MoveBall (HDC fon)
    {
    Ball ball1 = {50, 50, 15, RGB (0, 255, 255), RGB (0, 255, 255), 5, 2, 1};

    Platform platforma = {0, txGetExtentX ()*0.25, RGB(250, 250, 250)};


    int score = 0;

    int life = 5;

    while (life > 0)
        {
        txBegin ();

        txBitBlt  (txDC(), 0, 0, 600, 800, fon, 0, 0);

        TabloScore (&score);
        TablLife (&life);

        ball1.DrawBall ();
        platforma.Draw ();

        PhysicsBall(&ball1, platforma.x, platforma.widthX, &score, &life);

        Control(&platforma);

        txSleep(20);



        }

    txDeleteDC (fon);
    txSetColor(RGB (0, 255, 255));
    txSelectFont ("Comic Sans MS", 70);
    txTextOut (150, 350, "GAME OVER");

    }


//-----------------------------------------------------------------------------

void TabloScore (int* score)
    {
    txSetColor(TX_WHITE);
    txSelectFont ("Comic Sans MS", 30);
    txTextOut (50, 25, "БАЛЛЫ : ");
    txLine(0,                  100, txGetExtentX(),           100);

    char strScore [20] = "";
    sprintf (strScore, "%d", *score);

    txSetColor(RGB (0, 255, 255));
    txSelectFont ("Comic Sans MS", 30);
    txTextOut (200, 25, strScore);


    }

//-----------------------------------------------------------------------------

void TablLife (int* life)
    {

    txSetColor(TX_WHITE);
    txSelectFont ("Comic Sans MS", 30);
    txTextOut (400, 25, "ЖИЗНИ : ");

    char strLife [20] = "";
    sprintf (strLife, "%d", *life);

    txSetColor(RGB (0, 255, 255));
    txSelectFont ("Comic Sans MS", 30);
    txTextOut (550, 25, strLife);
    }

//-----------------------------------------------------------------------------


void PhysicsBall(Ball* ball1, double x, double widthX, int* score, int* life)
    {
    ball1->x = ball1->x + ball1->vx * ball1->dt;
    ball1->y = ball1->y + ball1->vy * ball1->dt;


    if (ball1->x > txGetExtentX() - ball1->radius)
        {
        ball1->vx = -(ball1->vx);
        ball1->x  = txGetExtentX() - ball1->radius;
        }

    if (ball1->x < ball1->radius)
        {
        ball1->vx = -(ball1->vx);
        ball1->x = ball1->radius;
        }


    if (ball1->y< 100 + ball1->radius)
        {
        ball1->vy = -(ball1->vy);
        ball1->y  = 100 + ball1->radius;
        }


    if (ball1->y > txGetExtentY() - 120 - ball1->radius)
        {
        switch (ball1->x > x && ball1->x < x + widthX)
            {
            case true:
                    ball1->vy = -(ball1->vy);
                    ball1->vx =   ball1->vx + 0.1;
                    ball1->y  = txGetExtentY() - 120 - ball1->radius;
                    *score  = *score + 1;
                    //txPlaySound ("Sounds/ball1.wav");

                break;

            case false:
                ball1->y  = 1000;
                *life = *life - 1;;
                //txPlaySound ("Sounds/gameOver.wav");
                break;

            default:
                break;
            }
        }
    }

//-----------------------------------------------------------------------------

void Control(Platform* platforma)
    {
    if (txGetAsyncKeyState (VK_RIGHT) and (platforma->x + platforma->widthX < txGetExtentX ())) platforma->x = platforma->x + 5;
    if (txGetAsyncKeyState (VK_LEFT) and (platforma->x > 0) ) platforma->x = platforma->x - 5;
    //if (txGetAsyncKeyState (VK_UP))    ball1->vy = ball1->vy - 1;
    //if (txGetAsyncKeyState (VK_DOWN))  ball1->vy = ball1->vy + 1;

    //if (txGetAsyncKeyState (VK_SPACE)) ball1->vx = ball1->vy = 0;
    }


//-----------------------------------------------------------------------------

void DrawField ()
    {
    txSetFillColor (TX_WHITE);
    txClear();


    txSetColor     (RGB(153, 102, 255));
    txSetFillColor (RGB(153, 102, 255));
    txRectangle (0,                   0, txGetExtentX(),           100);
    txRectangle (0, txGetExtentY() - 100, txGetExtentX(), txGetExtentY());

    }
