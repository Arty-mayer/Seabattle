#ifndef FIELD_H
#define FIELD_H

#include <Arduino.h>
#include "Ship.h"
#include "Crosshair.h"
#include "UnitShip.h"

#define SHIP_1 1
#define SHIP_2_L 2
#define SHIP_2_M 3
#define SHIP_2_R 4
#define SHIP_2_U 5
#define SHIP_2_VM 6
#define SHIP_2_D 7
#define VOID 8
#define MISS 9
#define HITED_SHIP 10

namespace SeaBattle
{

    class GameField
    {
    public:
        GameField();
        bool shipAdd(Ship *ship);
        uint8_t getCell(uint8_t x, uint8_t y);
        bool schoot(uint8_t x, uint8_t y);
        bool isHited();
        bool isDead();
        void diagOut();
        uint8_t getShipsCountByType(uint8_t type);

    private:
        void markAround(uint8_t x, uint8_t y, uint8_t mark);
        void markDeadShip (uint8_t x, uint8_t y, uint8_t pos, uint8_t lng, uint8_t sNum);

        // variables
        bool hited = false;
        bool shipDead = false;
        uint8_t cells[10][10];
        uint8_t ships[10][10];
       // uint8_t mode = 0;
        uint8_t shipsCountByType[4];
        uint8_t shipsCount; 
        

        UnitShip *unitShip[10];
    };
}
#endif