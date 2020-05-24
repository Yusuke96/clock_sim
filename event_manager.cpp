#include "main.hpp"

EM::EM(){;}
EM::~EM(){vector<pair<double,double>>.swap(events);}

double EM::Register(double time,double range){        
  pair<double,double> e; //イベント
  e.first = time;             //開始時刻
  e.second = e.first + range; //終了時刻

  //イベント挿入
  if(events.back().second <= e.first){
    events.push_back(e);
  }else{//エラー
    cout << "Error: Incorrect event insert at " << e.first << "." << endl;
    exit(-1);
  }
  
}

void EM::Show_events(){
  auto it = events.begin(); //イテレータ
  long i=0;
  while(it != events.end()){
    cout << "Event " << i << "\t" << *it.first << " ~ " << *it.second << endl; 
  }
  
}
