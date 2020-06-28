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
  int current_cache_num; // 現在処理中のストリームの辞書格納先
  int current_entry_size;// 現在処理中のストリームの格納先エントリサイズ
  int current_dict_size; // 現在処理中のストリームの辞書サイズ
  bool once_flg; // 初めのevent setで使用。true -> false

  // func
  Decmod();
  ~Decmod();
  void inQueue(Packet p); // パケットキューの外部用セッタ
  void deQueue();
  void tableAccess();
  void tableUpdate();
  void cacheAccess();
  void cacheRead();
  void cacheWrite();
  void dramAccess();
  void dramRead();
  void decode();
  void writeback();
  void none();
};
