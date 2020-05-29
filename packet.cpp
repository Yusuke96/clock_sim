#include "main.hpp"

Packet::Packet(){
  //Default
  timestamp = 0.0;
  length = 0;
  sip[0] = 0, sip[1] = 0, sip[2] = 0, sip[3] = 0;
  dip[0] = 0, dip[1] = 0, dip[2] = 0, dip[3] = 0;
  sport = 0, dport = 0;
  protocol = 0;
  comp_len = 0;
  decomp_len =0;
  comp_ratio = 0.0;
  stream_id = "";
  stream_size = 0;
  //Additional
  id = 0;
}

Packet::~Packet(){;}

void Packet::Show(){
  cout << "---------- Packet " << id << " ----------" << endl;  
  cout << "timestamp: " << timestamp << endl;
  cout << "length: " << length << endl;
  cout << "sip: " << (int)sip[0] << "." << (int)sip[1] << "." << (int)sip[2] << "." << (int)sip[3] << endl;
  cout << "dip: " << (int)dip[0] << "." << (int)dip[1] << "." << (int)dip[2] << "." << (int)dip[3] << endl;
  cout << "sport: " << sport << endl;
  cout << "dport: " << dport << endl;
  cout << "protocol: " << protocol << endl;
}
