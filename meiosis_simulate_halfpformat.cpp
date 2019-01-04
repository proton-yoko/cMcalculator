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

	int chr_flag = 0; //現在染色体ペアの0番目か1番目のどちらをコピーしているのか
	double memo = 0.0;
	double now = 0.0; //現在読んでいる行のmapの値
	int cnt = 0; //inputファイルの難行目について扱ってるのかcounter

	chr_flag = coin(mt);
	

	//vector<string> items;
	while (getline(p1, line1)){
		cnt++;

		//最初のコメント部はスキップ
		if(line1[0]=='#'){
			cout << line1 << endl;
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
			double random_score = score(mt);
			if(random_score < now-memo){
				if(chr_flag==0){
					chr_flag=1;
				}else{
					chr_flag=0;
				}
			}
			memo = now;
		}



	

		//chr_flagの通りに遺伝子情報を出力
		if(chr_flag == 0){
			cout << items1[0] << ' ' << items1[1] << ' ' << items1[2] << ' ' << items1[3] << ' ' << items1[4] << ' ' 
				<< items1[5].substr(0,1) << ' ' << items1[6] << ' ' << 0 << endl;
		}else{
			cout << items1[0] << ' ' << items1[1] << ' ' << items1[2] << ' ' << items1[3] << ' ' << items1[4] << ' '
				<< items1[5].substr(2,1) << ' ' << items1[7] << ' ' << 1 << endl;
		}


	
	}

	return 0;
}
