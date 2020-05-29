#include "main.hpp"

class Decmod{
private:
  vector<Packet> queue;
public:
  Decmod();
  ~Decmod();
  void inQueue(Packet p);
  void deQueue(Packet p);
};
