//mixer.cpp
//pformat.txtひとつから、減数分裂後の遺伝子をシミュレートする

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <array>
#include <random>

using namespace std;
int main(int argc, char **argv)
{
	//the usage of this program
	if(argc != 3){
		cout << "the usage of this program is like './a.out input_pformat1.txt chrxx.txt (>> output.txt)'" << endl;
		exit(1);
	}


	//ファイル入力チェック		
	ifstream p1(argv[1], ios::in);
	if(!p1){
		cerr << "Unable to open" << argv[1] << endl;
		exit(1);
	}	
	ifstream map(argv[2], ios::in);
	if(!map){
		cerr << "Unable to open" << argv[2] << endl;
		exit(1);
	}	

	//乱数生成準備部
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<int> coin(0,1);
	uniform_real_distribution<double> score(0.0, 100.0);

	string line1, mapline;
	string tmp;

	int match_flag = 0; 
//	double sum = 0.0; //shared cMの現時点での合計値
//	double start = 0.0;
	double memo = 0.0;
	double now = 0.0; //現在読んでいる行のmapの値
	int cnt = 0; //inputファイルの難行目について扱ってるのかcounter

	array<int, 200> chr; //中身は0で初期化されている
	//左なら0右なら1


	chr[0]

	//vector<string> items;
	while (getline(p1, line1)){
		cnt++;
		//getline(p2, line2);

		//最初のコメント部はスキップ
		if(line1[0]=='#'){
			//cout << line << endl;
			continue;
		}
		
		//一行について空白区切でitemsに格納する
		vector<string> items1;
		istringstream stream1(line1);
		while(getline(stream1, tmp, ' ')){
			items1.push_back(tmp);
		}

		//mapから一行読み込み
		getline(map, mapline);
		vector<string> mapitems;
		istringstream stream(mapline);
		while(getline(stream, tmp, ' ')){
			mapitems.push_back(tmp);
		}
		now = stod(mapitems[2]);
		
		//遺伝子名がマッチしていないとき終了
		if(items1[1].compare(mapitems[1])){
			cerr << "mismatch with map line" << endl;
			exit(1);
		}

		if(abs(stoi(items1[8])-stoi(items2[8]))!=2){
			//cout << "match" << ' '  << items1[5] << ' ' << items2[5] << endl;
			if(!match_flag){//初めて一致したとこ
				start = stod(mapitems[2]);
//				cout << "start -- " << start << endl;
				match_flag = 1;
			}
		}else{
			//cout << items1[5] << ' ' << items2[5] << endl;
			//if(match_flag){//一致がおわったとこ
			//end = stod(mapitems[2]);
			if(match_flag){
//				cout << "end ---- " << now << endl;
//				cout << "++++++++++++++++++++++++++++end - start " << now - start << endl;
				if(now - start > 1){
					sum += now;
					sum -= start;
					cout << "start / now / sum : " << start << " / " << now << " / " << sum << endl; 
					for(int i=(int)start+1; i<=(int)now; i++){
						chr[i]=1;
					}
				}
				match_flag = 0;
			}
		}
		



		
	}

	//cout << "end  " << now << "  start  " << start << endl;
	if(match_flag){
		if(now - start > 1){
			sum += now;
			sum -= start;
			cout << "start / now / sum : " << start << " / " << now << " / " << sum << endl;
			for(int i=(int)start+1; i<=(int)now; i++){
				chr[i]=1;
			}
			
		}
	}

	

		

	for(int i=0; i<=int(now); i++){
		if(chr[i]){
			cout << "X" ;
		}else{
			cout << "-" ;
		}
	}
	cout << endl;

	return 0;
}
