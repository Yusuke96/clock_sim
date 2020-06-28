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
  //results
  long cache_hit;
  long cache_miss;
  double time_start;
  double time_end;
  double proc_size;
  double throughput;
  //
  long num_of_packets;
  long cache_capacity;
  bool *decmod_empty;
  bool trace_empty;
  //Objects
  Selector* selector;
  Decmod* decmod;
  Table* table;
  Cache* cache;
  Dram* dram;
  //---------------関数-----------------
  Global();
  ~Global();
  void readConf(int argc, char *argv[]);
  void showConf();
  void initSim();
  bool runSelector(double start_time);
  bool runDecmod(double start_time);
  bool checkComplete();
  void reportResult();
};
