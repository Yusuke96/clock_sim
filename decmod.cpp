#include "main.hpp"

Decmod::Decmod(){;}
Decmod::~Decmod(){;}

void Decmod::inQueue(Packet p){
  this->q_decmod.push(p);
}

Packet Decmod::deQueue(Packet p){
  Packet p  = this->q_decmod.front(p);
  this->q_decmod.pop();
  return p;
}

void Decmod::decode(Packet& p){
  p.timestamp += global.delay_decode;
}
