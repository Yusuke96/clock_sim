#include "main.hpp"

class Global{
 public:
  //---------------変数-----------------
  //コンフィグファイル関連
  string tracefile;
  string resfile;//使ってないかも
  u_int num_cache;//キャッシュモジュールの数
  vector<u_int> cache_assign;// configのCACHEASSIGN
  map<u_int,u_int> cache_conf;//key=モジュールのエントリサイズ,
                        //val=そのエントリサイズを持つキャッシュモジュール数
  u_int num_decmod;
  double delay_decode;
  double delay_makehuff;
  double delay_table;
  double delay_cache;
  double delay_dram;
  u_int size_queue;
  //clock
  double clock_cycle;
  //Objects
  Selector* selector;
  Decmod* decmod;
  
  //---------------関数-----------------
  Global();
  ~Global();
  void readConf(int argc, char *argv[]);
  void showConf();
  void initSim();
  bool runSelector(double start_time);
  bool runDecmod(double start_time);
};
