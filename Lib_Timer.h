#ifndef TIMER_H
#define TIMER_H
 #include <Arduino.h>

 class Timer {
  public: 

  Timer (unsigned long time) ; //constructor
 
  void setTime (unsigned long time);
  void timerStart();
  void timerStop();
  void tick ();
  bool isTimerEnd();
  bool isTimerOn();
  
  

  private: 
  
  bool timerEnd;
  bool timerOn;
  unsigned long ttime;
  unsigned long t0;
};
#endif