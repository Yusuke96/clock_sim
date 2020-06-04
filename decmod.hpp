#include "main.hpp"

class Decmod{
private:
  //std::queue<Packet> q_decmod;
  bool busy;// false:free , true:busy
public:
  queue<Packet> q_decmod;
  u_int mod_num;
  pair<double,void (Decmod::*)()> next_event;
  Packet current_packet; // 現在処理中のパケット
  bool once_flg; // 初めのevent setで使用。true -> false
  // func
  Decmod();
  ~Decmod();
  void inQueue(Packet p); // パケットキューの外部用セッタ
  void deQueue();
  void cacheAccess();
  void cacheRead();
  void cacheWrite();
  void dramAccess();
  void dramRead();
  void decode();
  void writeback();
};
