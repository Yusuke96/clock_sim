#include "main.hpp"

class Selector{
private:
  ifstream trace;
  queue<Packet> q_selector; // パケットキュー
  long packet_id;
  double first_timestamp;// 一番初めに読み込まれたパケットのタイムスタンプ
public:
  Selector();
  ~Selector();
  void openTracefile();
  bool inputPacket(double start_time,double end_time);
  bool allocatePacket();
};
