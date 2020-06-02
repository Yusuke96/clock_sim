#include "main.hpp"

class Cache{
private:
  bool busy; // false=free , true=busy
public:
  Cache();
  ~Cache();
  bool access();
  void read();
  void write();
};
