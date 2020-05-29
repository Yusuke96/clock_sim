#include "main.hpp"

Clock::Clock(){
    time=0.0; 
}

Clock::~Clock(){;}

double Clock::GetTime(){
    return time;
}

void Clock::Advance(){
  time = time + global.clock_cycle; //クロック周波数を1GHzとしている
}
