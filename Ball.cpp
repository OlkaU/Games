#include "TXlib.h"

void MoveBall ();


int main ()
    {
    txCreateWindow (800, 600);

    MoveBall ();

    return 0;

    }

void MoveBall ()
    {
    int x  = 50, y  = 50,
        vx = 5,  vy = 2,
        ax = 1,  ay = 1;

    int dt = 1;
    txSetColor (RGB(255, 0, 255), 2);
    txSetFillColor (RGB (138, 43, 226));

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetColor (RGB(x, y, 255), 2);
        txSetFillColor (RGB (x/2, y/2, 255));

        txCircle (x, y, 15);

        vx += ax * dt;
        vy += ay * dt;

        x += vx * dt;
        y += vy * dt;

        if (x > 800)
            {
            vx = -vx;
            x  = 800;
            }

         if (y > 600)
            {
            vy = -vy;
            y  = 600;
            }

         if (x < 0)
            {
            vx = -vx;
            x  = 0;
            }

         if (y < 0)
            {
            vy = -vy;
            y  = 0;
            }

        if (txGetAsyncKeyState (VK_RIGHT)) vx++;
        if (txGetAsyncKeyState (VK_LEFT))  vx--;
        if (txGetAsyncKeyState (VK_UP))    vy--;
        if (txGetAsyncKeyState (VK_DOWN))  vy++;

        if (txGetAsyncKeyState (VK_SPACE)) vx = vy = 0;

        txSleep(10);
        }
    }
