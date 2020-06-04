#include "main.hpp"

class Dram{
private:
  map<size_t,u_int> table; // <stream_hash,no means>
public:
  double next_time_r;
  Dram();
  ~Dram();
  bool Access(Packet& p);
};
