#include "TXlib.h"

void MoveBall    ();
void DrweBall    (int x, int y, COLORREF bodyColor, COLORREF contourColor);
void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int dt);
void Control     (int* vx, int* vy);


int main ()
    {
    txCreateWindow (800, 600);

    MoveBall ();

    return 0;

    }

void MoveBall ()
    {
    int x1  = 50, y1  = 50,
        vx1 = 5,  vy1 = 3,
        ax1 = 0,  ay1 = 1;

    int x2  = 10, y2  = 10,
        vx2 = 3,  vy2 = 2,
        ax2 = 1,  ay2 = 1;

    int dt = 1;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        DrweBall (x1, y1, RGB (75, 0,   130), RGB (138, 43, 226));
        DrweBall (x2, y2, RGB (0,  255, 255), RGB (0,   0,  255));

        PhysicsBall(&x1, &y1, &vx1, &vy1, ax1, ay1, dt);
        PhysicsBall(&x2, &y2, &vx2, &vy2, ax2, ay2, dt);

        Control(&vx1, &vy1);

        txSleep(10);
        }
    }

//=============================================================================

void DrweBall(int x, int y, COLORREF bodyColor, COLORREF contourColor)
    {
    txSetColor (bodyColor, 2);
    txSetFillColor (contourColor);

    txCircle (x, y, 15);
    }

//-----------------------------------------------------------------------------

void PhysicsBall(int* x, int* y, int* vx, int* vy, int ax, int ay, int dt)
    {
    *vx = *vx + ax * dt;
    *vy = *vy + ay * dt;

    *x = *x + *vx * dt;
    *y = *y + *vy * dt;

    if (*x > 800)
        {
        *vx = -*vx;
        *x  = 800;
        }

    if (*y > 600)
        {
        *vy = -*vy;
        *y  = 600;
        }

    if (*x < 0)
        {
        *vx = -*vx;
        *x  = 0;
        }

    if (*y < 0)
        {
        *vy = -*vy;
        *y  = 0;
        }
    }

//-----------------------------------------------------------------------------

void Control(int* vx, int* vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) *vx = *vx + 1;
    if (txGetAsyncKeyState (VK_LEFT))  *vx = *vx - 1;
    if (txGetAsyncKeyState (VK_UP))    *vy = *vy - 1;
    if (txGetAsyncKeyState (VK_DOWN))  *vy = *vy + 1;

    if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = 0;
    }

