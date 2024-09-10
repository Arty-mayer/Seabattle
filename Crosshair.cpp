
#include "Crosshair.h"
 SeaBattle::Crosshair::Crosshair(){}

 void SeaBattle::Crosshair::timerTick()
 {
    timer.tick();
 }

 void SeaBattle::Crosshair::timerRestart()
 {
    timer.timerStart();
 }

 bool SeaBattle::Crosshair::timerIsEnd()
 {
     return timer.isTimerEnd();
 }

bool SeaBattle::Crosshair::moveH(bool left)
{
    if (!timer.isTimerEnd())
        return false;
    timer.timerStart();
    if (left)
    {
        if (x > 0)
            x--;
    }
    else
    {
        if (x < 9)
            x++;
    }
    return true;
}

bool SeaBattle::Crosshair::moveV(bool up)
{
    if (!timer.isTimerEnd())
        return false;
    timer.timerStart();
    if (up)
    {
        if (y > 0)
            y--;
    }
    else
    {
        if (y < 9)
            y++;
    }
    return true;
}

uint8_t SeaBattle::Crosshair::getX()
{
    return x;
}

uint8_t SeaBattle::Crosshair::getY()
{
    return y;
}

