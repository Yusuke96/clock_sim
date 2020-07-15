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
    if(current_time < global.next_time){
      global.clock->SetTime(global.next_time);
    }else{
      global.runSelector(current_time);
      global.runDecmod(current_time);
      global.clock->Advance();
    }
  }

  global.reportResult();
  
  return 0;
}
