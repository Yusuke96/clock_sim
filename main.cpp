#include "main.hpp"

Global global;

int main(int argc, char *argv[]){
  Clock clock;
  //Packet p;
  global.readConf(argc, argv);
  global.showConf();
  //global.initSim;

  // while(){
  //   double current_time=clock.GetTime();
  //   //decmod.process(current_time);
  //   clock.Advance();//time += 0.000001
  //   break;
  // }

  return 0;
}
