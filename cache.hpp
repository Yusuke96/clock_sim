#include "main.hpp"

class Cache{
private:
  //bool busy; // false=free , true=busy
  //size_t entry[1];// エントリ数とそのエントリに入っている辞書のStream_ID
public:
  vector<size_t> entry;
  u_int cache_num;
  u_int num_entry;
  u_int size_entry;
  Cache();
  ~Cache();
  bool access(Packet);
};
