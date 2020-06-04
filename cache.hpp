#include "main.hpp"

class Cache{
private:
  //bool busy; // false=free , true=busy
  //size_t entry[1];// エントリ数とそのエントリに入っている辞書のStream_ID
public:
  size_t entry[1];
  u_int cache_num;
  Cache();
  ~Cache();
  bool access(Packet);
};
