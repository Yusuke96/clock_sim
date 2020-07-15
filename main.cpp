#include "main.hpp"

Global global;

int main(int argc, char *argv[]){
  // setup
  global.readConf(argc, argv);
  global.showConf();
  global.initSim();
  global.selector->openTracefile();
  // main
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
  // result
  global.reportResult();
  
  return 0;
}
