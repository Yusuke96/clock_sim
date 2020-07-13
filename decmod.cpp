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
  if(!this->q_decmod.empty()){
    cout << "*Decmod[" << this->mod_num << "]: deQueue" << endl;
    this->current_packet  = this->q_decmod.front();
    this->q_decmod.pop();
    global.proc_size += this->current_packet.length;
    this->next_event.first += global.clock_cycle;
    //this->next_event.second = &Decmod::cacheAccess;
    this->next_event.second = &Decmod::tableAccess;
    global.decmod_empty[this->mod_num] = false;
  }else{
    cout << "*Decmod[" << this->mod_num << "]: wait(Q is empty)" << endl;
    this->next_event.first += global.clock_cycle;
    this->next_event.second = &Decmod::deQueue;
    global.decmod_empty[this->mod_num] = true;
  }
}

void Decmod::tableAccess(){
  cout << "*Decmod[" << this->mod_num << "]: tableAccess" << endl;
  if(global.table[this->mod_num].access(this->current_packet.hash) == -2){//table miss
    // streamの先頭パケット
    this->next_event.first = global.clock_cycle + global.delay_table;
    this->next_event.second = &Decmod::decode;
  }else{
    // streamの後続パケット
    this->current_cache_num = global.table[this->mod_num].m[this->current_packet.hash].first;
    this->current_dict_size = global.table[this->mod_num].m[this->current_packet.hash].second;
    this->next_event.first = global.clock_cycle + global.delay_table;
    if(this->current_cache_num != -1){
      this->next_event.second = &Decmod::cacheAccess;
    }else{
      this->current_packet.hit = false;
      global.cache_miss++;
      this->next_event.second = &Decmod::dramAccess;
    }
  }
}

void Decmod::cacheRead(){
  //cout << "cacheRead" << endl;
  this->next_event.first += global.delay_cache;
  this->next_event.second = &Decmod::decode;
}

void Decmod::dramRead(){
  //cout << "dramRead" << endl;
  this->next_event.first += global.delay_dram;
  this->next_event.second = &Decmod::decode;
}

void Decmod::decode(){
  cout << "*Decmod[" << this->mod_num << "]: decode" << endl;
  // 辞書サイズの更新
  this->current_dict_size += this->current_packet.decomp_len;
  if(this->current_dict_size >= 32000){this->current_dict_size = 32000;} // 辞書サイズは最大で32KB
  // 格納先の計算
  int cache_num_S=0, cache_num_L=7; // キャッシュ番号 cache_num_S ~ cache_num_L のいずれかに格納できる 
  for(int i=global.num_decmod-1; i==0; i--){ // 範囲外の参照してない？
    if(this->current_dict_size < int(global.cache[i].size_entry)){
      cache_num_L = i;
      continue;
    }else{
      if(this->current_dict_size > int(global.cache[i].size_entry)){
	cache_num_S = i-1;
	break;
      }else{
	continue;
      }
    }
  }
  this->current_cache_num = cache_num_S + (this->current_packet.hash % (cache_num_L - cache_num_S+1));
  this->current_entry_size = global.cache[this->current_cache_num].size_entry;
  //イベント登録
  this->next_event.first += global.delay_decode;
  this->next_event.second = &Decmod::cacheWrite;
}

void Decmod::writeback(){
  //シミュレーション開始直後にエントリが空の場合はめんどくさいので今は考慮しない
  //cout << "writeBack" << endl;
  global.table[this->mod_num].m[this->current_packet.hash].first = -1;
  this->next_event.first += global.delay_cache;
  this->next_event.second = &Decmod::cacheWrite;
}

void Decmod::cacheWrite(){
  cout << "*Decmod[" << this->mod_num << "]: cacheWrite" << endl;
  // 辞書格納(LRU)
  size_t tmp_cache_index = this->current_cache_num;
  // cacheから追い出しが発生する場合(write back)
  if(*global.cache[this->current_cache_num].entry.begin() != this->current_packet.hash){
    // 追い出されたストリームの格納先をDRAMに指定
    global.table[this->mod_num].m[*global.cache[this->current_cache_num].entry.begin()].first = -1;
    //this->current_cache_num = -1; // -1 == DRAM これいる？？
    this->next_event.first += global.delay_cache + global.delay_table;
  }
  // エントリの置換
  //cout << "current_cache_num: " << this->current_cache_num << endl;
  //cout << "tmp_cache_num: " << tmp_cache_index << endl;
  global.cache[tmp_cache_index].entry.erase(global.cache[tmp_cache_index].entry.begin());
  global.cache[tmp_cache_index].entry.push_back(this->current_packet.hash);
  this->next_event.first += global.delay_cache;
  this->next_event.second = &Decmod::tableUpdate;
}

void Decmod::tableUpdate(){// どこにいれよう
  cout << "*Decmod[" << this->mod_num << "]: tableUpdate" << endl;
  global.table[this->mod_num].update(this->current_packet.hash,this->current_cache_num,current_dict_size);
  // トランザクションの最後であるため、キューに次のパケットがあるか確認
  if(this->q_decmod.empty()){
    global.decmod_empty[this->mod_num] = true;
  }else{
    global.decmod_empty[this->mod_num] = false;
  }
  this->next_event.first += global.delay_table;
  this->next_event.second = &Decmod::deQueue;
}

void Decmod::cacheAccess(){ // 使わない? その場合tablaAccessでキャッシュヒット率の計算が必要
  cout << "*Decmod[" << this->mod_num << "]: cacheAccess" << endl;
  if(global.cache[this->current_cache_num].access(this->current_packet)){
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

void Decmod::dramAccess(){
  cout << "*Decmod[" << this->mod_num << "]: dramAccess" << endl;
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

