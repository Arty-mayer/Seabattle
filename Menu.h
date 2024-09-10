#pragma once
#include "Lib_Timer.h"

namespace SeaBattle
{
    class Menu
    {

    public:
        Menu();

        unsigned int getMenuCode();

        bool optionChanging(bool revers); // переключение опции

        bool isActive();       // возвращает menuOn - статус меню (активно/спит)
        bool addOption(byte count);      // добавить пункт меню (в конец массива)
        bool getChangStatus(); // возращает true если была смена опции и переводит этот ключь в false
        bool activation();
        bool setCheckedOption(byte option);
        bool getTimerIsEnd();
        void timerRestart();
        byte getCheckedOption(); // возвращает состояние changed, если оно true , то переводит его в false

        void setMenuCode(unsigned int code);
        void menuTimersTick(); // функция проверки таймеров меню

        void setMenuTime(unsigned long time); // устанавливает длительность паузы до следующей возможной смены option
                                              // void deleteOptions();
        // переменные
      
    private:
        unsigned int menuCode = 0;


        byte checkedOption;
        byte optionsCount = 0;

        Timer menuTimer = Timer(300);
        bool changed;
    };
}