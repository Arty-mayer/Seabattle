#ifndef UNITSHIP_H
#define UUNITSHIP_H

#include <Arduino.h>

namespace SeaBattle {
    class UnitShip
    {
    private:
        uint8_t health;
        uint8_t lang;
        uint8_t position;
        
    public:
        UnitShip(uint8_t lang, uint8_t position);
        bool isDeath();
        void hit();
        uint8_t getPosition ();
        uint8_t getLang();
    
    };
    
    
}

#endif