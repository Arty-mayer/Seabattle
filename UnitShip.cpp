#include "UnitShip.h"

SeaBattle::UnitShip::UnitShip( uint8_t lang, uint8_t position) : health(lang), lang(lang), position(position)
{
}

bool SeaBattle::UnitShip::isDeath()
{
    if (health == 0)
        return true;
    return false;
}

void SeaBattle::UnitShip::hit()
{
    if (health > 0) {
        health -- ; 
    }
}

uint8_t SeaBattle::UnitShip::getPosition()
{
    return position;
}

uint8_t SeaBattle::UnitShip::getLang()
{
    return lang;
}
