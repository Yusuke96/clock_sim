#include "main.hpp"

Cache::Cache(){  
}

Cache::~Cache(){;}

bool Cache::access(Packet p){
  p.timestamp += global.clock_cycle;
  if(this->entry[0] == p.hash){ // キャッシュヒット
    global.cache_hit++;
    return true;
  }else{ // キャッシュミス
    global.cache_miss++;
    return false;
  }
}

