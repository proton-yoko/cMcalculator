//mixer.cpp
//pformat.txtひとつから、減数分裂後の遺伝子をシミュレートする

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
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
	uniform_int_distribution<int> coin(0,1);
	uniform_real_distribution<double> score(0.0, 100.0);

	string line1, mapline;
	string tmp;

//	int match_flag = 0; 
	int chr_flag = 0; //現在染色体ペアの0番目か1番目のどちらをコピーしているのか
//	double sum = 0.0; //shared cMの現時点での合計値
//	double start = 0.0;
	double memo = 0.0;
	double now = 0.0; //現在読んでいる行のmapの値
	int cnt = 0; //inputファイルの難行目について扱ってるのかcounter

	int chr[200]; //中身は0で初期化されている
	//左なら0右なら1
	for(int i=0; i<200; i++){
		chr[i]=0;
	}

	//染色体ペアのどちらからコピーを始めるかをランダムに選択	
	chr[0] = coin(mt);
	chr_flag = chr[0];
	cout << "chr[0]=" << chr[0] << endl; 

	

	//vector<string> items;
	while (getline(p1, line1)){
		cnt++;
		//getline(p2, line2);

		//最初のコメント部はスキップ
		if(line1[0]=='#'){
			//cout << line << endl;
		//	cnt--;
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


		//100遺伝子に一度組み換えするかどうかランダムに決める
		if(cnt%5000 == 0){
			for(int i=(int)memo+1; i<=(int)now; i++){
				chr[i]=chr_flag;
			}
			cout << "cnt " << cnt << " memo now " << memo << " " << now << endl;
			double random_score = score(mt);
			cout << "random " << random_score << " now-memo " << now-memo << endl;
			if(random_score < now-memo){
				cout << "------------------------kumikae" << endl;
				if(chr_flag==0){
					chr_flag=1;
				}else{
					chr_flag=0;
				}
			}
			memo = now;
		}



	

/*		//chr_flagの通りに遺伝子情報を出力
		if(chr_flag == 0){
			cout << items1[0] << ' ' << items1[1] << ' ' << items1[2] << ' '
				<< items1[5].substr(0,1) << ' ' << items1[6] << ' ' << 0 << endl;
		}else{
			cout << items1[0] << ' ' << items1[1] << ' ' << items1[2] << ' '
				<< items1[5].substr(2,1) << ' ' << items1[7] << ' ' << 0 << endl;
		}

*/
	
	}


	for(int i=(int)memo+1; i<=(int)now; i++){
		chr[i]=chr_flag;
	}


	//組み換えを可視化
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
