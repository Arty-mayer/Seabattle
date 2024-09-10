#include "Field.h"

SeaBattle::GameField::GameField()
{
    for (uint8_t x = 0; x < 10; x++)
    {
        for (uint8_t y = 0; y < 10; y++)
        {
            cells[x][y] = 0;
            ships[x][y] = 255;
        }
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        shipsCountByType[i] = 0;
    }
    shipsCount = 0;

    /*  cells [5][5] = 1;

      cells [3][2] = 2;
      cells [4][2] = 3;
      cells [5][2] = 3;
      cells [6][2] = 4;

      cells [8][8] = 2;
      cells [9][8] = 4;

      cells [8][3] = 5;
      cells [8][4] = 6;
      cells [8][5] = 6;
      cells [8][6] = 7;

      cells [2][7] = 5;
      cells [2][8] = 7;*/
}

bool SeaBattle::GameField::shipAdd(Ship *ship)
{
    uint8_t maxX;
    uint8_t maxY;
    if (ship->position == 0)
    {
        maxX = 10 - ship->lng;
        maxY = 9;
    }
    else
    {
        maxX = 9;
        maxY = 10 - ship->lng;
    }
    if (ship->x > maxX || ship->y > maxY)
    {
        return false;
    }
    for (uint8_t i = 0; i < ship->lng; i++)
    {
        if (ship->position == 0)
        {
            if (cells[ship->x + i][ship->y] != 0)
            {
                return false;
            }
        }
        else
        {
            if (cells[ship->x][ship->y + i] != 0)
            {
                return false;
            }
        }
    }

    if (ship->lng < 2)
    {

        cells[ship->x][ship->y] = SHIP_1;
        ships[ship->x][ship->y] = shipsCount;
        markAround(ship->x, ship->y, VOID);

        unitShip[shipsCount] = new UnitShip(ship->lng, ship->position);
        shipsCountByType[ship->lng - 1]++;
        shipsCount++;
        return true;
    }

    for (uint8_t i = 0; i < ship->lng; i++)
    {
        if (ship->position == 0)
        {
            if (i == 0)
            {
                cells[ship->x + i][ship->y] = SHIP_2_L;
                ships[ship->x + i][ship->y] = shipsCount;
                markAround(ship->x + i, ship->y, VOID);
            }
            else if (i + 1 == ship->lng)
            {
                cells[ship->x + i][ship->y] = SHIP_2_R;
                ships[ship->x + i][ship->y] = shipsCount;
                markAround(ship->x + i, ship->y, VOID);
            }
            else
            {
                cells[ship->x + i][ship->y] = SHIP_2_M;
                ships[ship->x + i][ship->y] = shipsCount;
                markAround(ship->x + i, ship->y, VOID);
            }
        }

        else
        {
            if (i == 0)
            {
                cells[ship->x][ship->y + i] = SHIP_2_U;
                ships[ship->x][ship->y + i] = shipsCount;
                markAround(ship->x, ship->y + i, VOID);
            }
            else if (i + 1 == ship->lng)
            {
                cells[ship->x][ship->y + i] = SHIP_2_D;
                ships[ship->x][ship->y + i] = shipsCount;
                markAround(ship->x, ship->y + i, VOID);
            }
            else
            {
                cells[ship->x][ship->y + i] = SHIP_2_VM;
                ships[ship->x][ship->y + i] = shipsCount;
                markAround(ship->x, ship->y + i, VOID);
            }
        }
    }
    unitShip[shipsCount] = new UnitShip(ship->lng, ship->position);
    shipsCountByType[ship->lng - 1]++;
    shipsCount++;
    return true;
}

uint8_t SeaBattle::GameField::getCell(uint8_t x, uint8_t y)
{
    return cells[x][y];
}

bool SeaBattle::GameField::schoot(uint8_t x, uint8_t y)
{
    if (cells[x][y] == 0 || cells[x][y] == VOID)
    {
        cells[x][y] = MISS;
        hited = false;
        return true;
    }
    if (cells[x][y] > 0 && cells[x][y] < 8)
    {
        cells[x][y] = HITED_SHIP;
        uint8_t shipsNum = ships[x][y];
        unitShip[shipsNum]->hit();
        if (unitShip[shipsNum]->isDeath())
        {
            shipDead = true;
            shipsCount--;
            shipsCountByType[unitShip[shipsNum]->getLang() - 1]--;
            markDeadShip(x, y, unitShip[shipsNum]->getPosition(), unitShip[shipsNum]->getLang(), shipsNum);
        }
        else
        {
            shipDead = false;
        }
        hited = true;
        return true;
    }
    hited = false;
    return false;
}

bool SeaBattle::GameField::isHited()
{
    return hited;
}

bool SeaBattle::GameField::isDead()
{
    return shipDead;
}
/*
void SeaBattle::GameField::diagOut()
{
    // for (uint8_t y = 0; y < 10; y++)
    //  {
    for (uint8_t x = 0; x < 10; x++)
    {
        Serial.print(x);
        Serial.print("=");
        Serial.println(ships[x][0]);
    }
    // }
}*/

uint8_t SeaBattle::GameField::getShipsCountByType(uint8_t type)
{
    if (type > 3)
        return 0;
    return shipsCountByType[type];
}

void SeaBattle::GameField::markAround(uint8_t x, uint8_t y, uint8_t mark)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (x + i == 0 || x + i - 1 > 9)
        {
            continue;
        }
        for (uint8_t z = 0; z < 3; z++)
        {
            if (y + z == 0 || y + z - 1 > 9)
            {
                continue;
            }
            if (cells[x + i - 1][y + z - 1] == 0 || cells[x + i - 1][y + z - 1] == VOID)
            {
                cells[x + i - 1][y + z - 1] = mark;
            }
        }
    }
}

void SeaBattle::GameField::markDeadShip(uint8_t x, uint8_t y, uint8_t pos, uint8_t lng, uint8_t sNum)
{
    uint8_t count = 0;

    for (uint8_t i = 0; i < 10; i++)
    {
    
        if (pos == HORIZONTAL)
        {
            if (ships[i][y] == sNum)
            {
             
                markAround(i, y, MISS);
                count++;
            }
        }
        else
        {
            if (ships[x][i] == sNum)
            {
                markAround(x, i, MISS);
                count++;
            }
        }
        //  if (count > lng)
        //   {
        //      break;
        //  }
    }
}
