#include "main.hpp"

Selector::Selector(){
  packet_id = 0;
}

Selector::~Selector(){;}

void Selector::openTracefile(){
  ifstream trace_tmp;
  string line;
  trace_tmp.open(global.tracefile.c_str(),ifstream::in);
  while(getline(trace_tmp,line)){
    global.num_of_packets++;
  }
  trace_tmp.close();
  trace.open(global.tracefile.c_str(),ifstream::in);
  if(!trace.is_open()){
    cout << "[Selector::openTracefile] Error: Trace file can not opend." << endl;
  }
}

bool Selector::inputPacket(double start_time, double end_time){
  while(true){
    Packet p;
    string line;
    packet_id++;
    auto oldpos = trace.tellg(); //イテレータを記録

    //一行読み込み
    getline(trace, line);
    if(trace.eof()){
      global.trace_empty = true;
      return false;
    }//読み込むパケット無し
    p.id = packet_id;
    //値の格納
    istringstream is, ip;
    string sip, dip;
    is.str(line);
    is >> p.timestamp >> p.length >> sip >> dip >> p.protocol >> p.sport >> p.dport >> p.comp_len >> p.decomp_len >> p.comp_ratio >> p.stream_id >> p.stream_size;

    //一番初めのパケットの時刻を0とし、以降それとの差分でシミュレーションを行う
    if(p.id == 1){
      first_timestamp = p.timestamp;
      p.timestamp = 0.0;
    }else{
      p.timestamp = p.timestamp - first_timestamp ;
    }
    if(start_time <= p.timestamp && p.timestamp < end_time){
      p.timestamp += global.clock_cycle;
      q_selector.push(p);
    }else{
      packet_id --;
      trace.seekg(oldpos); // 現在処理するべきパケットではないので記録した位置までイテレータを戻して終了
      break;
    }
  }
  return true;
}

bool Selector::allocatePacket(){
  if(!q_selector.empty()){
    Packet p = q_selector.front();
    std::string sip = p.sip;
    std::string dip = p.dip;
    std::string f_tuple = sip + dip + to_string(p.sport) + to_string(p.dport) + to_string(p.protocol);
    size_t hash = std::hash<std::string>()(f_tuple);
    int mod_num = int(hash % global.num_decmod);
    p.hash = hash;
    p.timestamp += global.clock_cycle;
    q_selector.pop();
    //cout << p.timestamp << endl;
    global.decmod[mod_num].inQueue(p); // 参照渡し?
    
    if(global.decmod[mod_num].q_decmod.empty() || global.decmod[mod_num].once_flg == true){
      global.decmod[mod_num].next_event.first = p.timestamp + global.clock_cycle;
      global.decmod[mod_num].next_event.second = &Decmod::deQueue;
      global.decmod[mod_num].once_flg = false;
    }
    return true;
  }else{
    return false;//queue is empty
  }
}

