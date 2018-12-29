//pcompmap2.cpp
//pformat.txtとhapmapを比較してshared cMの値を計算する
//可視化してわかりやすくしたい
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <array>
using namespace std;
int main(int argc, char **argv)
{
	if(argc != 4){
		cout << "the usage of this program is like './a.out input_pformat1.txt input_pformat2.txt chrxx.interpolated_genetic_map (>> output.txt)'" << endl;
		exit(1);
	}

	//ファイル入力チェック		
	ifstream p1(argv[1], ios::in);
	if(!p1){
		cerr << "Unable to open" << argv[1] << endl;
		exit(1);
	}	
	ifstream p2(argv[2], ios::in);
	if(!p2){
		cerr << "Unable to open" << argv[3] << endl;
		exit(1);
	}	
	ifstream map(argv[3], ios::in);
	if(!map){
		cerr << "Unable to open" << argv[3] << endl;
		exit(1);
	}	



	string line1, line2, mapline;
	string tmp;

	int match_flag = 0;
	double sum = 0.0;
	double start = 0.0;
//	double end = 0.0;
	double now = 0.0;
	int cnt = 0;

	array<int, 200> chr;
//	int chr[200];
//	for(int i=0; i<200; i++){
//		chr[i]=0;
//	}

	//vector<string> items;
	while (getline(p1, line1)){
		cnt++;
//		cout << cnt << endl;
		getline(p2, line2);

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
		vector<string> items2;
		istringstream stream2(line2);
		while(getline(stream2, tmp, ' ')){
			items2.push_back(tmp);
		}


		//遺伝子名がマッチしていないとき終了
		if(items1[2].compare(items2[2])){
			cerr << "something went wrong" << endl;
			exit(1);
		}

		
//		if(items1[2].substr(0,2).compare("rs")){
//			continue;
//		}

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

	
	cout << "end  " << now << "  start  " << start << endl;
	cout << "last score is " << sum << endl;

		

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
