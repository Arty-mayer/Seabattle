#include "Game.h"

namespace SeaBattle
{

    GameSeaBattle::GameSeaBattle()
    {
        gameInitialil();
        gameStarted = false;
        gameScreen = 0;
        gfx.drawScr();
    }

    GameSeaBattle::~GameSeaBattle()
    {
        gameEnd();
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        delay(300);
    }

    void GameSeaBattle::gameInitialil()
    {
        menu = nullptr;
        field1 = nullptr;
        field2 = nullptr;
        enemyesShootXY[0] = 0;
        enemyesShootXY[1] = 0;
    }

    void GameSeaBattle::menuHandler()
    {
        menudraw = false;
        if (menu == nullptr)
        {
            menuCreate();
            if (gameStarted)
            {
                gfx.drawPauseMenu(menu->getCheckedOption());
                gfx.drawScr();
            }
            else
            {
                gfx.drawMenu(menu->getCheckedOption(), speed);
                gfx.drawScr();
            }
        }
        menu->menuTimersTick();

        if (btn_rt.btnState() || btn_lt.btnState())
        {
            menudraw = menu->optionChanging(btn_lt.btnState());
        }
        if (btn_up.btnState() || btn_dn.btnState())
        {
            menudraw = menuOptionChange(btn_dn.btnState());
        }
        if (btn_st.btnState())
        {
            menuOptionActivation();
        }
        if (menudraw)
        {
            if (gameStarted)
            {

                gfx.drawPauseMenu(menu->getCheckedOption());
                gfx.drawScr();
            }
            else
            {
                gfx.drawMenu(menu->getCheckedOption(), speed);
                gfx.drawScr();
            }
        }
    }

    bool GameSeaBattle::menuOptionChange(bool revers)
    {
        if (gameStarted)
        {
            return false;
        }
        if (menu->getCheckedOption() == 2)
        {
            if (menu->getTimerIsEnd())
            {
                menu->timerRestart();
                speed = (revers) ? speed - 1 : speed + 1;
                if (speed < 1)
                {
                    speed = 1;
                }
                if (speed > 15)
                {
                    speed = 15;
                }
                return true;
            }
        }

        return false;
    }

    void GameSeaBattle::menuCreate()
    {
        if (menu != nullptr)
        {
            return;
        }
        menu = new Menu;
        if (gameStarted)
        {
            menu->addOption(2);
        }
        else
        {
            menu->addOption(3);
        }
    }

    void GameSeaBattle::menuOptionActivation()
    {
        if (gameStarted)
        {
            switch (menu->getCheckedOption())
            {
            case 1:
                gameResume();
                break;
            case 2:
                gameEnd();
                break;
            }
        }
        else
        {
            switch (menu->getCheckedOption())
            {
            case 1:
                gameStart();
                break;
            case 3:
                gameExit();
                break;
            }
        }
    }

    void GameSeaBattle::gameStart()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }

        // to do написать стартер
        if (field1 != nullptr)
        {
            delete field1;
            field1 = nullptr;
        }
        if (field2 != nullptr)
        {
            delete field2;
            field2 = nullptr;
        }
        gameMode = MODE_PLACEMENT;
        field1 = new GameField;
        field2 = new GameField;
        shipRestForPlacing = 10;
        gameStarted = true;
        timerFrame.timerStart();
        // timerGameStep.timerStart();
        gameScreen = 1;

        delay(200);
    }

    void GameSeaBattle::gamePause()
    {
        timerFrame.timerStop();
        gameScreen = 0;
        delay(300);
    }

    void GameSeaBattle::gameResume()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        delay(500);
        timerFrame.timerStart();
        gameScreen = 1;
    }

    void GameSeaBattle::gameEnd()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        timerFrame.timerStop();
        gameStarted = false;
        gameScreen = 0;

        delay(300);
    }

    void GameSeaBattle::gameExit()
    {
        exit = true;
        gameEnd();
    }

    void GameSeaBattle::gameOver()
    {
        gameStarted = false;
        // timerFrame.timerStop();
    }

    void GameSeaBattle::mainLoop()
    {
        if (exit)
        {
            return;
        }
        if (gameScreen == 0)
        {
            menuHandler();
            return;
        }
        // timerGameStep.tick();

        timerFrame.tick();
        timerEnemy.tick();
        if (gameMode == MODE_PLACEMENT)
        {
            handlerplacement();
        }
        if (gameMode == MODE_BATTLE)
        {
            if (crossHair != nullptr)
                crossHair->timerTick();
            handlerBattle();
        }

        if (timerFrame.isTimerEnd())
        {
            timerFrame.timerStart();

            drawScreen();

            if (btn_esc.btnState())
            {
                gamePause();
            }
        }
    }

    void GameSeaBattle::drawScreen()
    {
        if (gameMode == MODE_PLACEMENT)
        {
            gfx.drawField1(field1);
            if (ship != nullptr)
            {
                gfx.drawShip(ship);
            }
            gfx.drawPlacemenedShips(shipRestForPlacing);
        }
        if (gameMode == MODE_BATTLE)
        {
            gfx.drawField1(field1);
            gfx.drawField2(field2);
            gfx.drawCannons();
            gfx.drawCrosshair(crossHair);
            gfx.printXY(crossHair->getX(), crossHair->getY(), false);
            gfx.printXY(enemyesShootXY[0], enemyesShootXY[1], true);
            
            uint8_t ar1[4]; uint8_t ar2[4];
            for (uint8_t i = 0 ; i <4; i++){
                ar1[i] = field1->getShipsCountByType(i);
                ar2[i] = field2->getShipsCountByType(i);
            }
            gfx.printStatistic(ar1,ar2);
        }

        gfx.drawScr();
    }

    void GameSeaBattle::addEnemyes()
    {

        if (ship != nullptr)
        {
            delete ship;
            ship = nullptr;
        }
        uint8_t l = 0;
        uint8_t x;
        uint8_t y;
        for (uint8_t i = 10; i > 00; i--)
        {
            if (i > 9)
                l = 4;
            if (i < 10)
                l = 3;
            if (i < 8)
                l = 2;
            if (i < 5)
                l = 1;
            if (l > 0)
                switch (i)
                {
                case 1:
                    x = 0;
                    y = 0;
                    break;
                case 2:
                    x = 0;
                    y = 2;
                    break;
                case 3:
                    x = 0;
                    y = 6;
                    break;
                case 4:
                    x = 0;
                    y = 8;
                    break;
                case 5:
                    x = 8;
                    y = 0;
                    break;
                case 6:
                    x = 5;
                    y = 0;
                    break;
                case 7:
                    x = 5;
                    y = 3;
                    break;
                case 8:
                    x = 5;
                    y = 5;
                    break;
                case 9:
                    x = 5;
                    y = 7;
                    break;
                case 10:
                    x = 5;
                    y = 9;
                    break;
                }
            ship = new Ship(l, 0);
            ship->x = x;
            ship->y = y;
            field2->shipAdd(ship);
        }
       // field2->diagOut();
    }

    bool GameSeaBattle::getExit()
    {
        return exit;
    }

    void GameSeaBattle::handlerplacement()
    {
        //shipRestForPlacing = 1;
        if (ship == nullptr)
        {
            uint8_t l = 0;
            if (shipRestForPlacing > 9)
            {
                l = 4;
            }
            if (shipRestForPlacing < 10)
            {
                l = 3;
            }
            if (shipRestForPlacing < 8)
            {
                l = 2;
            }
            if (shipRestForPlacing < 5)
            {
                l = 1;
            }
            if (l > 0)
            {
                ship = new Ship(l, 0);
            }
        }
        ship->timersTick();

        if (btn_lt.btnState() || btn_rt.btnState())
        {
            ship->moveHoriyontal(btn_lt.btnState());
        }
        if (btn_up.btnState() || btn_dn.btnState())
        {
            ship->moveVertical(btn_up.btnState());
        }
        if (btn_md.btnState())
        {
            ship->changePosition();
        }
        if (btn_st.btnState())
        {
            if (field1->shipAdd(ship))
            {
                delete ship;
                ship = nullptr;
                shipRestForPlacing--;
                delay(200);
            }
        }
        if (shipRestForPlacing == 0)
        {
            addEnemyes();
            if (crossHair != nullptr)
            {
                delete crossHair;
                crossHair = nullptr;
            }
            crossHair = new Crosshair;
            gameMode = MODE_BATTLE;
            crossHair->timerRestart();
        }
    }
    void GameSeaBattle::handlerBattle()
    {
        if (enemysShoot)
        {
            EnemysHandler();
        }
        else
        {
            playersHandler();
        }
    }
    void GameSeaBattle::playersHandler()
    {
        if (btn_lt.btnState() || btn_rt.btnState())
        {
            crossHair->moveH(btn_lt.btnState());
        }
        if (btn_up.btnState() || btn_dn.btnState())
        {
            crossHair->moveV(btn_up.btnState());
        }
        if (btn_st.btnState())
        {
            if (crossHair->timerIsEnd() && field2->schoot(crossHair->getX(), crossHair->getY()))
            {
                crossHair->timerRestart();
                gfx.drawShoot(false);
                if (field2->isHited())
                {
                    gfx.drawExplosion(crossHair->getX(), crossHair->getY(), false);
                }
                else
                {
                    enemysShoot = true;
                    timerEnemy.timerStart();
                }
            }
        }
    }
    void GameSeaBattle::EnemysHandler()
    {
        if (!timerEnemy.isTimerEnd())
        {
            return;
        }
        uint8_t x = random(0, 11);
        uint8_t y = random(0, 11);
        if (field1->schoot(x, y))
        {
            enemyesShootXY[0] = x;
            enemyesShootXY[1] = y;
            gfx.drawShoot(true);
            if (field1->isHited())
            {
                timerEnemy.timerStart();

                gfx.drawExplosion(x, y, true);
            }
            else
            {
                enemysShoot = false;
            }
        }
    }

}