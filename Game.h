#include <Arduino.h>

#include "Lib_Button.h"
#include "Menu.h"
#include "Gfx.h"
#include "MP_Game.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Field.h"
#include <MemoryFree.h>
#include "Ship.h"
#include "Crosshair.h"

#define MODE_BATTLE 2
#define MODE_PLACEMENT 1



extern Button btn_lt;
extern Button btn_rt;
extern Button btn_dn;
extern Button btn_up;
extern Button btn_st;
extern Button btn_esc;
extern Button btn_md;

namespace SeaBattle
{

    class GameSeaBattle : public Game
    {

    public:
        GameSeaBattle(); // constructor
        ~GameSeaBattle();

        void mainLoop();

        byte speed = 1;
        bool getExit();

    private:
        
        void AIShoot();
        void drawScreen();
        void addEnemyes();

        void gameScores(byte SCount);

        void handlerplacement();
        void handlerBattle();
        void playersHandler();
        void EnemysHandler();

    
       
        // game Menu
        void menuCreate();
        void menuOptionActivation();
        bool menuOptionChange(bool revers);
        void menuHandler();
 
        // game control
        void gameStart();
        void gameInitialil();
        void gamePause();
        void gameResume();
        void gameEnd();
        void gameExit();
        void gameOver();

        // variables
        bool exit = false;


        bool menudraw;
        bool gameStarted;
        uint8_t gameScreen;
        uint8_t gameMode; 
        uint8_t shipRestForPlacing;
        uint8_t enemyesShootXY[2];

       bool enemysShoot = false;



       
        GameField *field1 = nullptr;
        GameField *field2 = nullptr;
        Crosshair *crossHair = nullptr;
        Ship *ship = nullptr; 
        Menu *menu = nullptr;
        Timer timerFrame = Timer(50);
        Timer timerEnemy = Timer (1000);
        

        Gfx gfx = Gfx();
    };
}