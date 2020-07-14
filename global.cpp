#include "main.hpp"
#include <iomanip>

Global::Global(){
  //----------変数の初期化----------
  //コンフィグファイル関連
  tracefile="";
  num_decmod=0;
  delay_decode=0.0;
  delay_makehuff=0.0;
  delay_table=0.0;
  delay_dram=0.0;
  size_queue=0;
  //clock cycle
  clock_cycle = 0.00001;
  //results
  cache_hit = 0;
  cache_miss = 0;
  time_start = 0.0;
  time_end = 0.0;
  //
  num_of_packets = 0;
  cache_capacity = 32; //******************************
  trace_empty = false;
}

Global::~Global(){

}

void Global::readConf(int argc, char *argv[]){
  //file open
  if(argc >= 2){
    istringstream is;
    string line, tag, val;
    ifstream conffile(argv[1], ifstream::in);
    //エラー処理
    if(!conffile.is_open()){
      cout << "[Global::readconf] Error: Config file does not exist." << endl;
    }
  
    //コンフィグファイルの内容を変数に格納
    while(getline(conffile, line)){
      if(line.size() == 0){continue;}
      is.clear(), tag = "", val = ""; // tag = 項目名, val = 値
      is.str(line);
      is >> tag >> val;
      //tag比較部分（マッチしたtagの値を変数に代入）
      if(!tag.compare("TRACEFILE")){tracefile = val;}
      if(!tag.compare("RESFILE")){resfile = val;}
      if(!tag.compare("CACHENUMBER")){num_cache = (u_int)stoi(val);}
      if(!tag.compare("CACHEASSIGN")){
	for(u_int n=0; n<num_cache; n++){
	  u_int i = (u_int)stoi(val);
	  cache_assign.push_back(i);
	  is >> val;
	}
      }
      if(!tag.compare("DECMODNUMBER")){num_decmod = (u_int)stoi(val);}
      if(!tag.compare("GZIPDECDLAY")){delay_decode = stod(val);}
      if(!tag.compare("MAKEHUFFDELAY")){delay_makehuff = stod(val);}
      if(!tag.compare("QUEUESIZE")){size_queue = (u_int)stoi(val);}
      if(!tag.compare("TABLEDELAY")){delay_table = stod(val);}
      if(!tag.compare("CACHEDELAY")){delay_cache = stod(val);}
      if(!tag.compare("DRAMDELAY")){delay_dram = stod(val);}
    }
    //file close
    conffile.close();
  }else{
    //コマンドライン引数の不足
    cout << "[Global::readconf] Error: the number of arguments is inappropriate." << endl;
  }
}

void Global::showConf(){
  cout << "--------------------CONFIG--------------------" << endl;
  cout << "TRACEFILE " << tracefile << endl;
  cout << "RSFILE " << resfile << endl;
  cout << "CACHENUMBER " << num_cache << endl;
  cout << "CACHEASSIGN ";
  auto it = cache_assign.begin();
  for(u_int i=0; i<num_cache; i++){
    u_int tmp = *it;
    if(tmp == *it){cache_conf[tmp] = cache_conf[tmp] + 1;}
    it++;
  }
  auto itr = cache_conf.rbegin();
  while(itr != cache_conf.rend()){
    cout << itr->first << "KB:" << itr->second << " ";
    itr++;
  }
  cout << endl;
  cout << "DECMODNUMBER " << num_decmod << endl;
  cout << "QUEUESIZE " << size_queue << endl;
  cout << "GZIPDECDELAY " << delay_decode << endl;
  cout << "MAKEHUFFDELAY " << delay_makehuff << endl;
  cout << "TABLEDELAY " << delay_table << endl;
  cout << "CACHEDELAY " << delay_cache << endl;
  cout << "DRAMDELAY " << delay_dram << endl;
  cout << "----------------------------------------------" << endl;
}

void Global::initSim(){
  selector = new Selector;
  decmod = new Decmod[num_decmod];
  table = new Table[num_decmod];
  cache = new Cache[num_decmod];
  clock = new Clock;
  dram = new Dram;

  decmod_empty = new bool[num_decmod];
  
  for(u_int i=0; i<num_decmod; i++){
    decmod[i].mod_num = i;
    cache[i].cache_num = i;
    cache[i].num_entry = cache_capacity/cache_assign[i];
    cache[i].size_entry = cache_assign[i];
    cache[i].entry.resize(cache[i].num_entry);
    //cache[i].entry.push_back(0);
    global.decmod_empty[i] = false;
  }
}

bool Global::runSelector(double start_time){
  bool si,sa;
  si = selector->inputPacket(start_time,start_time + clock_cycle);
  sa = selector->allocatePacket();
  return si || sa;
}

bool Global::runDecmod(double start_time){
  for(u_int i=0; i<global.num_decmod; i++){
    if(decmod[i].next_event.first <= start_time && decmod[i].next_event.first > 0){
      //cout << "decmod:" << i << endl;
      void (Decmod::*func)() = decmod[i].next_event.second;
      (decmod[i].*func)();
    }
  }
  return true; // **
}

bool Global::checkComplete(){
  bool result = true;
  for(u_int i=0; i<num_decmod; i++){
    result = result && decmod_empty[i];
    //cout << decmod_empty[i] << " " ;
  }
  //cout << endl;
  return result;
}

void Global::reportResult(){
  float hit_rate = float(cache_hit) / (float(cache_hit) + float(cache_miss));
  for(u_int i=0;i<num_decmod;i++){
    if(time_end < decmod[i].next_event.first){
      time_end = decmod[i].next_event.first;
    }
  }
  cout << "--------------------RESULT--------------------" << endl;
  cout << cache_hit << ",  " << cache_miss << endl;
  cout << "Number of packets: " << num_of_packets << endl;
  cout << "Cache hit rate: " << hit_rate << " %" << endl;
  cout << "Dram access: " << dram_read << endl;
  cout << "Time: " << time_end << " sec" << endl;
  cout << "Decoding throughput: " << std::fixed << std::setprecision(5) << ((proc_size*8) / (time_end*1000*1000*1000)) << " Gbps" << endl;
  cout << "----------------------------------------------" << endl;
}

