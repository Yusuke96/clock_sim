#include "main.hpp"

class Table{
private:
public:
  map<size_t,std::pair<int,int>> m; //<cache_num,dict_size>
  int access(size_t hash);
  void update(size_t hash, int cache_num, int dict_size);
  Table();
  ~Table();
};
