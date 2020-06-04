#include "main.hpp"

Global global;

int main(int argc, char *argv[]){
  Clock clock;
  //Selector selector;
  //Packet p;
  global.readConf(argc, argv);
  global.showConf();
  global.initSim();
  global.selector->openTracefile();
  
  while(!global.checkComplete()){
    double current_time = clock.GetTime();
    global.runSelector(current_time);
    global.runDecmod(current_time);
    clock.Advance();
  }

  global.reportResult();
  
  return 0;
}
