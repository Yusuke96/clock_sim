#include "main.hpp"

class Decmod{
private:
  std::queue<Packet> q_decmod;
  bool busy;// false:free , true:busy
public:
  Decmod();
  ~Decmod();
  void inQueue(Packet p);
  Packet deQueue(Packet p);
  void decode(Packet& p);
  void accessDram(Packet p);
  void accessCache(Packet p);
};
