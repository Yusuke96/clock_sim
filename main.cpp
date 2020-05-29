#include "main.hpp"

Global global;

int main(int argc, char *argv[]){
  Clock clock;
  Selector selector;
  //Packet p;
  global.readConf(argc, argv);
  global.showConf();
  //global.initSim;
  selector.openTracefile();
  bool si;
  
  while(true){
    double current_time = clock.GetTime();
    si = selector.inputPacket(current_time, current_time + global.clock_cycle);
    //decmod.process(current_time);
    clock.Advance();
    if(!si){break;}
  }

  return 0;
}
