#include "main.hpp"

Decmod::Decmod(){
  once_flg = true;
}
Decmod::~Decmod(){;}

// 外部からのアクセッサ専用
void Decmod::inQueue(Packet p){
  this->q_decmod.push(p);
}

//--------------------------------------------------------------------
void Decmod::deQueue(){
  //cout << "deQueue" << endl;
  if(!this->q_decmod.empty()){
    this->current_packet  = this->q_decmod.front();
    this->q_decmod.pop();
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::cacheAccess;
  }else{
    global.decmod_empty[this->mod_num] = true;
  }
}

void Decmod::cacheAccess(){
  //cout << "cacheAccess" << endl;
  if(global.cache[this->mod_num].access(this->current_packet)){
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::cacheRead;
  }else{
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::dramAccess;
  }
}

void Decmod::cacheRead(){
  //cout << "cacheRead" << endl;
  this->next_event.first += global.delay_cache;
  this->next_event.second = &Decmod::decode;
}

void Decmod::cacheWrite(){
  cout << this->current_packet.id << endl;
  //cout << "cacheWrite" << endl;
  global.cache[this->mod_num].entry[0] = this->current_packet.hash;
  this->next_event.first += global.delay_cache;
  if(this->q_decmod.empty()){
    global.decmod_empty[this->mod_num] = true;
  }else{
    this->next_event.second = &Decmod::deQueue;
  }
}

void Decmod::dramAccess(){
  //cout << "dramAccess" << endl;
  if(this->next_event.first >= global.dram->next_time_r){
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::dramRead;
    global.dram->next_time_r += global.clock_cycle + global.delay_dram;
  }else{
    this->next_event.first = global.dram->next_time_r;
    this->next_event.second = &Decmod::dramAccess;
    global.dram->next_time_r += global.delay_dram;
  }
}

void Decmod::dramRead(){
  //cout << "dramRead" << endl;
  this->next_event.first += global.delay_dram;
  this->next_event.second = &Decmod::decode;
}

void Decmod::writeback(){
  //シミュレーション開始直後にエントリが空の場合はめんどくさいので今は考慮しない
  //cout << "writeBack" << endl;
  this->next_event.first += global.delay_cache;
  this->next_event.second = &Decmod::cacheWrite;
}

void Decmod::decode(){
  //cout << "decode" << endl;
  this->next_event.first += global.delay_decode;
  if(global.cache[this->mod_num].entry[0] == this->current_packet.hash){
    this->next_event.second = &Decmod::cacheWrite;
  }else{
    this->next_event.second = &Decmod::writeback;
  }
}

