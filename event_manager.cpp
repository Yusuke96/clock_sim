#include "main.hpp"

EM::EM(){
    vector<pair<double,double>> events;
}
EM::~EM(){
}

double EM::Register(double time,double range){        
    pair<double,double> e;
    e.first = time;//開始時刻
    e.second = e.first + range;//終了時刻
    events.push_back(e);
}

void EM::Show_events(){
}
