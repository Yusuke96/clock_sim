#include "main.hpp"

class Packet{
public:
  //トレースファイルに記載済みの情報
  double timestamp;
  u_int length;
  u_char sip[4];
  u_char dip[4];
  u_char protocol;
  u_int sport;
  u_int dport;
  long comp_len;
  long decomp_len;
  double comp_ratio;
  string stream_id;
  long stream_size;
  //シミュレータで付加した情報
  long id;
  //関数
  Packet();
  ~Packet();
  void Show();
};
