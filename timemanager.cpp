#include "main.hpp"

TM::TM(){
    vector<pair<double,double>> events;
}
TM::~TM(){
}

double TM::Access(double time,double range){
    pair<double,double> = e;
    //e.first = time;
    //e.second = e + range;
    if(time >= events.back.first){//追加するイベントが時刻順で一番新しい場合
	if(time >= events.back.second){//一個前のイベントと時刻が重ならず、一番新しい場合
	    e.first = time;
	    e.second = e + range;
	    events.push_back(e);
	}else{//一個前のイベントと時刻が一部重なる場合
	    e.first = events.back.second;//一個前のイベントの終了時刻を開始時刻に設定
	    e.second = e.first + range;
	    events.push_back(e);
	}
    }else{//追加するイベントが時刻順で一番新しくない場合
	auto it = events.begin();//iterator
	while(it != events.begin()){//時刻順の位置までイテレータを移動
	    if(time < *it.first){break;}
	    it--;
	}
	if(*it[-1].second <= time && time+range <= *it.first){//イベントを挿入しようとした時刻が空いており、問題なく挿入できる場合
	    e.first = time;
	    e.second = time + range;
	    events.insert(it-1,e);
	}else{//イベントを挿入しようとした時刻が他のイベントと被っている場合
	    if(*it[-1].second+range <= *it.first){//ストールして前のイベント終了を待つだけで解決する場合
		//ストール処理
		e.first = *it[-1].second;
		e.second = e.first + range;
		events.insert(it-1,e)
	    }else{//他イベントの移動が必要な場合
	    	//イベント移動処理
	    }
	}
    }

}
