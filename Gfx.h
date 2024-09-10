#ifndef GFX_H
#define GFX_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Field.h"
#include "imgs.h"
#include "Crosshair.h"

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

    class Gfx
    {
    public:
        Gfx();

        void drawScr();
        void drawMenu(byte selected, byte speed);
        void drawPauseMenu(byte selected);
        void drawBorder();

        void drawField1(GameField *field);
        void drawField2(GameField *field);
        void drawShip(Ship *ship);
        void drawPlacemenedShips(uint8_t rest);
        void drawCrosshair(Crosshair *ch);
        void drawCannons();
        void drawShoot(bool enemy);
        void drawExplosion(uint8_t x, uint8_t y, bool enemy);
        void printXY(uint8_t x, uint8_t y, bool enemy);
        void printStatistic(uint8_t *arr, uint8_t *arr2);

    private:
        const uint8_t *getMenusImg(uint8_t bildNum);
        const uint8_t *getCellsImg(uint8_t bildNum);
        const uint8_t *getFireAnimation();
        const uint8_t *getShootAnimation();
        const uint8_t *getEnemysShootAnimation();
        const uint8_t *getExploAnimation(uint8_t bildNum);

        void shootAnim(bool enemy);
        void explAnim();

        // vars
        uint8_t scrNum = 0;
        uint8_t animNum = 0;
        uint8_t shoot1 = 0;
        uint8_t shoot2 = 0;
        uint8_t explosion = 0;
        int explX = 0;
        int explY = 0;
    };
}
#endif
