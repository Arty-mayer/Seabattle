#include "Menu.h"

namespace SeaBattle
{

    Menu::Menu() : checkedOption(1), optionsCount(0) {
        menuTimer.timerStart();
    }

    unsigned int Menu::getMenuCode()
    {
        return menuCode;
    }

    void Menu::setMenuCode(unsigned int code)
    {
        menuCode = code;
    }

    bool Menu::optionChanging(bool revers)
    {
        if (menuTimer.isTimerEnd())
        {
            menuTimer.timerStart();
           
                switch (revers)
                {
                case true:
                    if (checkedOption <= 1)
                    {

                        checkedOption = 1;
                        return false;
                    }
                    else
                    {
                        checkedOption = checkedOption - 1;
                    }
                    break;
                default:
                    if (checkedOption >= optionsCount)
                    {

                        checkedOption = optionsCount;
                        return false;
                    }
                    else
                    {
                        checkedOption = checkedOption + 1;
                    }
                    break;
                }
            
            changed = true;
            return true;
        }
        return false;
    }

    void Menu::menuTimersTick()
    {
        menuTimer.tick();
    }

    byte Menu::getCheckedOption()
    {
        return checkedOption;
    }

    bool Menu::getChangStatus()
    {
        if (changed)
        {
            changed = false;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Menu::addOption(byte count)
    {
        if (optionsCount+count >= 5)
        {
            return false;
        }
        optionsCount = optionsCount + count;
        return true;
    }

    void Menu::setMenuTime(unsigned long time)
    {
        menuTimer.setTime(time);
    }

    bool Menu::setCheckedOption(byte option)
    {
        if (option == 0 || option > optionsCount)
        {
            return false;
        }
        checkedOption = option;
        return true;
    }
    bool Menu::getTimerIsEnd()
    {
        return menuTimer.isTimerEnd();
    }
    void Menu::timerRestart()
    {
        menuTimer.timerStart();
    }
}