#include "main.hpp"

Clock::Clock(){
    time=0.0; 
}

Clock::~Clock(){;}

double Clock::GetTime(){
    return time;
}

void Clock::Advance(){
  time += 0.000001; //クロック周波数を1GHzとしている
}
