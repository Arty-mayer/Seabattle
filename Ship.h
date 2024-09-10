#ifndef SHIP_H
#define SHIP_H

#include <Arduino.h>
#include "Lib_Timer.h"

#define VERTIKAL 1
#define HORIZONTAL 0

namespace SeaBattle
{

    class Ship
    {
    private:
        Timer moveTimer = Timer (180);
    public:
        Ship(uint8_t lang, uint8_t pos);
        bool changePosition();
        bool moveVertical(bool up);
        bool moveHoriyontal(bool left);
        void timersTick();
        // vars
        uint8_t position;
        uint8_t lng;
        uint8_t x;
        uint8_t y;
    };

}
#endif
