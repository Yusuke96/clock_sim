#include "main.hpp"

class Global{
 public:
  //---------------変数-----------------
  //コンフィグファイル関連
  string tracefile;
  u_int num_decmod;
  double delay_decode;
  double delay_makehuff;
  double delay_table;
  double delay_dram;
  u_int size_queue;
  //---------------関数-----------------
  Global();
  ~Global();
  void readConf(int argc, char *argv[]);
};
