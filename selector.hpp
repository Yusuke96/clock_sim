#include "main.hpp"

class Selector{
private:
  ifstream trace;
  vector<Packet> queue; // パケットキュー
  long packet_id;
  double first_timestamp;// 一番初めに読み込まれたパケットのタイムスタンプ
public:
  Selector();
  ~Selector();
  void openTracefile();
  bool inputPacket(double start_time,double end_time);
  void allocatePacket(Packet p);
};
