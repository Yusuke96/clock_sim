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
      if(!tag.compare("DECMODNUMBER")){num_decmod = (u_int) stoi(val);}//5/25 いまここまで
      if(!tag.compare("GZIPDELAY")){delay_decode = stod(val);}
      if(!tag.compare("MAKEHUFFDELAY")){delay_makehuff = stod(val);}
      if(!tag.compare("QUEUESIZE")){size_queue = (u_int) stoi(val);}
      if(!tag.compare("TABLEDELAY")){delay_table = stod(val);}
      if(!tag.compare("DRAMDELAY")){delay_table = stod(val);}
    }
    //file close
    conffile.close();
  }else{
    //コマンドライン引数の不足
    cout << "[Global::readconf] Error: the number of arguments is inappropriate." << endl;
  }
}

