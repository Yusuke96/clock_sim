#include "main.hpp"

Table::Table(){}

Table::~Table(){}

int Table::access(size_t hash){
  if(this->m.count(hash) == 0){ // table miss
    return -1;
  }else{  // table hit
    return m.at(hash).first; //return cache_num(0~7) or dram(-1)
  }
}

void Table::update(size_t hash, int cache_num, int dict_size){
  pair<int,int> p;
  p.first = cache_num;
  p.second = dict_size;
  this->m[hash] = p;
}

