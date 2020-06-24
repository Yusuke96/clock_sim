#include "main.hpp"

Decmod::Decmod(){
  once_flg = true;
  this->next_event.first = -1.0;
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
    global.proc_size += this->current_packet.length;
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::cacheAccess;
  }else{
    global.decmod_empty[this->mod_num] = true;
  }
}

void Decmod::cacheAccess(){
  //cout << "cacheAccess" << endl;
  if(global.cache[this->mod_num].access(this->current_packet)){
    //cout << "hit" << endl;
    this->current_packet.hit = true;
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::cacheRead;
  }else{
    //cout << "miss" << endl;
    this->current_packet.hit = false;
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
  //cout << this->current_packet.id << endl;
  global.cache[this->mod_num].entry.erase(global.cache[this->mod_num].entry.begin());
  global.cache[this->mod_num].entry.push_back(this->current_packet.hash);
  if(this->q_decmod.empty()){
    global.decmod_empty[this->mod_num] = true;
  }else{
    this->next_event.first += global.delay_cache;
    this->next_event.second = &Decmod::deQueue;
  }
}

void Decmod::dramAccess(){
  //cout << "dram access" << this->current_packet.id << endl;
  //cout << this->next_event.first << " " << global.dram->next_time_r << endl;
  if(this->next_event.first >= global.dram->next_time_r){
    //cout << "*********************" << endl;
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::dramRead;
    global.dram->next_time_r += global.clock_cycle + global.delay_dram;
  }else{
    this->next_event.first = global.dram->next_time_r;
    this->next_event.second = &Decmod::dramRead;
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
  if(this->current_packet.hit == true){
    this->next_event.second = &Decmod::cacheWrite;
  }else{
    this->next_event.second = &Decmod::writeback;
  }
}

