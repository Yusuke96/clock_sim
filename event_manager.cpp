#include "main.hpp"

EM::EM(){;}
EM::~EM(){vector<pair<double,double>>.swap(events);}

double EM::Register(double time,double range){        
  pair<double,double> e; //イベント
  e.first = time;             //開始時刻
  e.second = e.first + range; //終了時刻
  events.push_back(e);
}

void EM::Show_events(){
  auto it = events.begin();
  long i=0;
  while(it != events.end()){
    cout << "Event " << i << "\t" << *it.first << " ~ " << *it.second << endl; 
  }
}
