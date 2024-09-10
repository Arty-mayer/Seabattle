#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Game.h"

#define OLED_RESET -1
// #define SCREEN_ADDRESS 0x3C
#include <MemoryFree.h>

// Adafruit_SSD1306 display(128,64,&Wire,OLED_RESET);

#define OLED_MOSI 50
#define OLED_CLK 52
#define OLED_DC 10
#define OLED_CS 53
#define OLED_RESET 51

Button btn_lt = Button(8, true);
Button btn_rt = Button(7, true);
Button btn_dn = Button(6, true);
Button btn_up = Button(5, true);
Button btn_st = Button(3, true);
Button btn_md = Button(4, true);
Button btn_esc = Button(2, true);

Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// using Tank::Game;

Game *game;
byte screen;
void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  displayInit();
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  screen = 0;
}

bool displayInit()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC)) //,SCREEN_ADDRESS))
  {
    delay(100);
    displayInit();
    display.clearDisplay();
    display.display();
  }
  else
  {
    return true;
  }
  return false;
}

void keyboardListener()
{
  btn_lt.buttonListener();
  btn_rt.buttonListener();
  btn_dn.buttonListener();
  btn_up.buttonListener();
  btn_st.buttonListener();
  btn_esc.buttonListener();
  btn_md.buttonListener();
}

void loop()
{
  keyboardListener();
  if (screen == 0)
  {
    if (btn_st.btnState())
    {

      screen = 2;
      game = new SeaBattle::GameSeaBattle;
    }
    return;
  }
  if (game->getExit())
  {
    if (game != nullptr)
    {
      delete game;
      game = nullptr;
    }
    screen = 0;
    delay(300);
  }
  if (game != nullptr)
  {
    game->mainLoop();
  }
}
