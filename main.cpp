#include "main.hpp"

Global global;

int main(int argc, char *argv[]){
  //Clock clock;
  //Selector selector;
  //Packet p;
  global.readConf(argc, argv);
  global.showConf();
  global.initSim();
  global.selector->openTracefile();
  
  while(!global.checkComplete() || !global.trace_empty){
    double current_time = global.clock->GetTime();
    global.runSelector(current_time);
    //cout << "p1" << endl;
    global.runDecmod(current_time);
    global.clock->Advance();
  }

  global.reportResult();
  
  return 0;
}
