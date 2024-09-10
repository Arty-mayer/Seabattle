#include "Gfx.h"

extern Adafruit_SSD1306 display;

namespace SeaBattle
{
    Gfx::Gfx() {}

    void Gfx::drawScr()
    {
        display.display();
        display.clearDisplay();
        scrNum++;
        if (scrNum > 3)
        {
            animNum = (animNum < 2) ? animNum + 1 : 0;
            scrNum = 0;
        }

        shootAnim(false);

        explAnim();
    }

    void Gfx::drawMenu(byte selected, byte speed)
    {
        for (byte i = 0; i < 3; i++)
        {
            display.drawBitmap(i * 24 + 16, 10, getMenusImg(i), 18, 18, 1);
        }
        byte xCor = (selected - 1) * 24 + 9 + 16;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
        display.setCursor(45, 30);
        display.print(speed);
    }
    void Gfx::drawPauseMenu(byte selected)
    {

        display.drawBitmap(40, 10, getMenusImg(10), 18, 18, 1);
        display.drawBitmap(64, 10, getMenusImg(2), 18, 18, 1);
        byte xCor = (selected - 1) * 24 + 9 + 40;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
    }

    void Gfx::drawBorder()
    {
        display.drawRect(0, 0, 102, 52, 1);
    }

    void Gfx::drawField1(GameField *field)
    {
        display.drawBitmap(0, 13, field_pic, 51, 51, 1);
        for (uint8_t x = 0; x < 10; x++)
        {
            for (uint8_t y = 0; y < 10; y++)
            {
                if (field->getCell(x, y) > 0 && field->getCell(x, y) != VOID)
                {
                    display.drawBitmap(x * 5, y * 5 + 13, getCellsImg(field->getCell(x, y)), 6, 6, 1);
                }
            }
        }
    }

    void Gfx::drawField2(GameField *field)
    {
        display.drawBitmap(77, 13, field_pic, 51, 51, 1);
        for (uint8_t x = 0; x < 10; x++)
        {
            for (uint8_t y = 0; y < 10; y++)
            {
                if (field->getCell(x, y) > 8 && field->getCell(x, y) != VOID)
                {
                    display.drawBitmap(x * 5 + 77, y * 5 + 13, getCellsImg(field->getCell(x, y)), 6, 6, 1);
                }
            }
        }
    }

    void Gfx::drawShip(Ship *ship)
    {
        if (ship->lng == 1)
        {
            display.drawBitmap(ship->x * 5, ship->y * 5 + 13, ship1, 6, 6, 1);
            return;
        }
        for (uint8_t i = 0; i < ship->lng; i++)
        {
            if (ship->position == 0)
            {
                if (i == 0)
                {
                    display.drawBitmap((ship->x + i) * 5, ship->y * 5 + 13, shipL, 6, 6, 1);
                }
                else if (i == ship->lng - 1)
                {
                    display.drawBitmap((ship->x + i) * 5, ship->y * 5 + 13, shipR, 6, 6, 1);
                }
                else
                {
                    display.drawBitmap((ship->x + i) * 5, ship->y * 5 + 13, shipM, 6, 6, 1);
                }
            }
            else
            {
                if (i == 0)
                {
                    display.drawBitmap(ship->x * 5, (ship->y + i) * 5 + 13, shipU, 6, 6, 1);
                }
                else if (i == ship->lng - 1)
                {
                    display.drawBitmap(ship->x * 5, (ship->y + i) * 5 + 13, shipD, 6, 6, 1);
                }
                else
                {
                    display.drawBitmap(ship->x * 5, (ship->y + i) * 5 + 13, shipMV, 6, 6, 1);
                }
            }
        }
    }

    void Gfx::drawPlacemenedShips(uint8_t rest)
    {
        for (uint8_t i = 0; i < rest; i++)
        {
            uint8_t y = 15;
            uint8_t z = 0;
            if (i > 4)
            {
                y = 35;
                z = 5;
            }
            if (i < 4)
            {
                display.drawBitmap(55 + (i - z) * 10, y, ship1, 6, 6, 1);
            }
            if (i > 3 && i < 7)
            {
                display.drawBitmap(55 + (i - z) * 10, y, shipU, 6, 6, 1);
                display.drawBitmap(55 + (i - z) * 10, y + 5, shipD, 6, 6, 1);
            }
            if (i > 6 && i < 9)
            {
                display.drawBitmap(55 + (i - z) * 10, y, shipU, 6, 6, 1);
                display.drawBitmap(55 + (i - z) * 10, y + 5, shipMV, 6, 6, 1);
                display.drawBitmap(55 + (i - z) * 10, y + 10, shipD, 6, 6, 1);
            }
            if (i == 9)
            {
                display.drawBitmap(55 + (i - z) * 10, y, shipU, 6, 6, 1);
                display.drawBitmap(55 + (i - z) * 10, y + 5, shipMV, 6, 6, 1);
                display.drawBitmap(55 + (i - z) * 10, y + 10, shipMV, 6, 6, 1);
                display.drawBitmap(55 + (i - z) * 10, y + 15, shipD, 6, 6, 1);
            }
        }
    }

    void Gfx::drawCrosshair(Crosshair *ch)
    {
        display.drawBitmap(ch->getX() * 5 + 75, ch->getY() * 5 + 11, crosshair, 10, 10, 1);
    }

    void Gfx::drawCannons()
    {
        display.drawBitmap(31, 4, cannon1, 20, 9, 1);
        display.drawBitmap(77, 4, cannon2, 20, 9, 1);
    }

    void Gfx::drawShoot(bool enemy)
    {
        if (enemy)
        {
            shoot2 = 1;
        }
        else
        {
            shoot1 = 1;
        }
    }

    void Gfx::drawExplosion(uint8_t x, uint8_t y, bool enemy)
    {
        if (enemy)
        {
            explosion = 1;
            explX = x * 5 - 1;
            explY = y * 5 + 10;
        }
        else
        {
            explosion = 1;
            explX = x * 5 + 74;
            explY = y * 5 + 10;
        }
    }

    void Gfx::printXY(uint8_t x, uint8_t y, bool enemy)
    {
        char tx;
        switch (x)
        {
        case 0:
            tx = 'a';
            break;
        case 1:
            tx = 'b';
            break;
        case 2:
            tx = 'c';
            break;
        case 3:
            tx = 'd';
            break;
        case 4:
            tx = 'e';
            break;
        case 5:
            tx = 'f';
            break;
        case 6:
            tx = 'g';
            break;
        case 7:
            tx = 'h';
            break;
        case 8:
            tx = 'i';
            break;
        case 9:
            tx = 'j';
            break;
        default:
            tx = ' ';
            break;
        }
        if (enemy)
        {
            display.setCursor(12, 4);
        }
        else
        {
            display.setCursor(108, 4);
        }
        display.print(tx);
        // display.print('-');
        display.print(y);
    }

    void Gfx::printStatistic(uint8_t *arr1, uint8_t *arr2)
    {
        display.setCursor (62,13);
        display.print('1');
        for (uint8_t i = 0; i < 4; i++)
        {
            
            display.setCursor(56, 22 + (i * 8));
            display.print(arr1[i]);
            display.print('|');
            //display.print(i+1);
           // display.print('|');
            display.print(arr2[i]);
        }
        display.setCursor (62,55);
        display.print('4');
    }

    const uint8_t *Gfx::getCellsImg(uint8_t bildNum)
    {
        switch (bildNum)
        {
        case SHIP_1:
            return ship1;
            break;

        case SHIP_2_L:
            return shipL;
            break;
        case SHIP_2_R:
            return shipR;
            break;
        case SHIP_2_M:
            return shipM;
            break;
        case SHIP_2_U:
            return shipU;
            break;
        case SHIP_2_D:
            return shipD;
            break;
        case SHIP_2_VM:
            return shipMV;
            break;
        case VOID:
            return voidCell;
            break;
        case MISS:
            return missedCell;
            break;
        case HITED_SHIP:
            return getFireAnimation();
            break;
        }
    }

    const uint8_t *Gfx::getFireAnimation()
    {
        switch (animNum)
        {
        case 0:
            return fire1;
            break;
        case 1:
            return fire2;
            break;
        case 2:
            return fire3;
            break;

        default:
            break;
        }
        return nullptr;
    }

    const uint8_t *Gfx::getShootAnimation()
    {
        switch (shoot1)
        {
        case 1:
            return shoot11;
            break;
        case 2:
            return shoot12;
            break;
        case 3:
            return shoot13;
            break;
        case 4:
            return shoot14;
            break;
        }
        return nullptr;
    }

    const uint8_t *Gfx::getEnemysShootAnimation()
    {
        switch (shoot2)
        {
        case 1:
            return shoot21;
            break;
        case 2:
            return shoot22;
            break;
        case 3:
            return shoot23;
            break;
        case 4:
            return shoot24;
            break;
        }
        return nullptr;
    }

    const uint8_t *Gfx::getExploAnimation(uint8_t bildNum)
    {
        switch (bildNum)
        {
        case 1:
            return expl1;
            break;
        case 2:
            return expl2;
            break;
        case 3:
            return expl3;
            break;
        case 4:
            return expl4;
            break;
        case 5:
            return expl2;
            break;
        }
        return nullptr;
    }

    void Gfx::shootAnim(bool enemy)
    {
        if (shoot1 > 0)
        {
            display.drawBitmap(51, 2, getShootAnimation(), 8, 11, 1);
            shoot1++;
        }
        if (shoot1 > 4)
        {
            shoot1 = 0;
        }

        if (shoot2 > 0)
        {
            display.drawBitmap(70, 2, getEnemysShootAnimation(), 8, 11, 1);
            shoot2++;
        }
        if (shoot2 > 4)
        {
            shoot2 = 0;
        }
    }

    void Gfx::explAnim()
    {
        if (explosion > 4)
        {
            display.drawBitmap(explX, explY, getExploAnimation(2), 11, 11, 1);
            explosion = 0;
        }
        if (explosion > 0 && explosion < 5)
        {
            display.drawBitmap(explX, explY, getExploAnimation(explosion), 11, 11, 1);
            explosion++;
        }
    }

    const uint8_t *Gfx::getMenusImg(byte bildNum)
    {
        switch (bildNum)
        {
        case 0:
            return manuStart;
            break;
        case 1:
            return menuSpeed;
            break;
        case 2:
            return menuOut;
            break;
        case 10:
            return menuBack;
            break;
        }
        return nullptr;
    }

}
