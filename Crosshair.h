#ifndef CROSSHAIR_H
#define CROSSHAIR_H
#include "Lib_Timer.h"

namespace SeaBattle
{
    class Crosshair
    {
    private:
        // vars
        uint8_t x = 4;
        uint8_t y = 4;
        Timer timer = Timer(120);

    public:
        Crosshair(/* args */);

        void timerTick();
        void timerRestart();
        bool timerIsEnd();
 

        bool moveH(bool left);
        bool moveV(bool up);

        uint8_t getX();
        uint8_t getY();
    };

}

#endif