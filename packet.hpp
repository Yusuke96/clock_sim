#include "main.hpp"

class Packet{
public:
  //トレースファイルに記載済みの情報
  double timestamp;
  u_int length;
  char sip[4];
  char dip[4];
  char protocol;
  u_int sport;
  u_int dport;
  long comp_len;
  long decomp_len;
  double comp_ratio;
  string stream_id;
  long stream_size;
  //シミュレータで付加した情報
  long id;
  size_t hash;
  //関数
  Packet();
  ~Packet();
  void Show();
};
