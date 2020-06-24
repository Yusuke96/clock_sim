#include "main.hpp"

Cache::Cache(){
}

Cache::~Cache(){;}

bool Cache::access(Packet p){
  p.timestamp += global.clock_cycle;
  // if(this->entry.size() < this->num_entry){
  //cout << "fp" << endl;
  //return true;
  //}
  for(auto it = this->entry.begin(); it != this->entry.end(); it++){
    if(*it == p.hash){
      this->entry.erase(it);
      this->entry.push_back(p.hash);
      global.cache_hit++;
      return true;
    }
  }
  global.cache_miss++;
  return false;
}

