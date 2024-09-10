#include "Ship.h"

SeaBattle::Ship::Ship(uint8_t lang, uint8_t pos) : position(pos), lng(lang), x(0), y(0) {}

bool SeaBattle::Ship::changePosition()
{
      if (!moveTimer.isTimerEnd())
      {
            return false;
      }
      moveTimer.timerStart();
      position = (position == HORIZONTAL) ? VERTIKAL : HORIZONTAL;
      if (position == HORIZONTAL)
      {
            if (x + lng > 10)
            {
                  x = 10 - lng;
            }
      }
      else
      {
            if (y + lng > 10)
            {
                  y = 10 - lng;
            }
      }
}

bool SeaBattle::Ship::moveVertical(bool up)
{
      if (!moveTimer.isTimerEnd())
      {
            return false;
      }
      moveTimer.timerStart();
      uint8_t dy = 1;
      if (position == VERTIKAL)
      {
            dy = lng;
      }
      if (up)
      {
            if (y > 0)
            {
                  y--;
                  return true;
            }
      }
      else
      {
            if (y < 10 - dy)
            {
                  y++;
                  return true;
            }
      }
      return false;
}

bool SeaBattle::Ship::moveHoriyontal(bool left)
{
      if (!moveTimer.isTimerEnd())
      {
            return false;
      }
      moveTimer.timerStart();
      uint8_t dx = 1;
      if (position == HORIZONTAL)
      {
            dx = lng;
      }
      if (left)
      {
            if (x > 0)
            {
                  x--;
                  return true;
            }
      }
      else
      {
            if (x < 10 - dx)
            {
                  x++;
                  return true;
            }
      }
      return false;
}

void SeaBattle::Ship::timersTick()
{
      moveTimer.tick();
}
