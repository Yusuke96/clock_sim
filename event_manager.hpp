#include "main.hpp"

class EM{
private:
  vector<pair<double,double>> events;

public:
  EM(); 
  ~EM();
  double Register(double,double);//イベントのセッター
  void Show_events(); //イベントのゲッター
  
};
