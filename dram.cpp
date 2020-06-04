#include "main.hpp"

Dram::Dram(){;}

Dram::~Dram(){;}

bool Dram::Access(Packet& p){
  if(this->table.count(p.hash) == 0){
    this->table[p.hash] = 1;
    return false;
  }else{
    return true;
  }
}
