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
      if(!tag.compare("GZIPDELAY")){delay_decode = stod(val);}
      if(!tag.compare("MAKEHUFFDELAY")){delay_makehuff = stod(val);}
      if(!tag.compare("QUEUESIZE")){size_queue = (u_int)stoi(val);}
      if(!tag.compare("TABLEDELAY")){delay_table = stod(val);}
      if(!tag.compare("CACHEDELAY")){delay_cache = stod(val);}
      if(!tag.compare("DRAMDELAY")){delay_table = stod(val);}
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
}

void Global::initSim(){
  selector = new Selector;
  decmod = new Decmod[num_decmod];
  //cache = new Cache[num_cache];
}

bool Global::runSelector(double start_time){
  bool si,sa;
  si = selector->inputPacket(start_time,start_time + clock_cycle);
  sa = selector->allocatePacket();
  return si || sa;
}

bool Global::runDecmod(double start_time){
  for(int i=0; i<global.num_decmod; i++){
    Packet p = decmod[i].q_decmod.front();
  }
}
