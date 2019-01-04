//mix_halfpformat.cpp
//2 halfpformat.txt >> 1 pformat.txt

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;
int main(int argc, char **argv)
{
	//the usage of this program
	if(argc != 3){
		cout << "the usage of this program is like './a.out halfpformat1.txt halfpformat2.txt (>> output.txt)'" << endl;
		exit(1);
	}


	//ファイル入力チェック		
	ifstream hp1(argv[1], ios::in);
	if(!hp1){
		cerr << "Unable to open" << argv[1] << endl;
		exit(1);
	}	
	ifstream hp2(argv[2], ios::in);
	if(!hp2){
		cerr << "Unable to open" << argv[2] << endl;
		exit(1);
	}	

	string line1, line2;
	string tmp;

	int cnt = 0; //inputファイルの難行目について扱ってるのかcounter

	while (getline(hp1, line1)){
		cnt++;
		getline(hp2, line2);

		//最初のコメント部はそのまま出力
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
		vector<string> items2;
		istringstream stream2(line2);
		while(getline(stream2, tmp, ' ')){
			items2.push_back(tmp);
		}

	
		//遺伝子名がマッチしていないとき終了
		if(items1[1].compare(items2[1])){
			cerr << "mismatch with map line" << endl;
			exit(1);
		}


	
		cout << items1[0] << ' ' << items1[1] << ' ' << items1[2] << ' '
			<< items1[3] << ' ' << items1[4] << ' ' 
			<< items1[5] << '|' << items2[5] << ' ' 
			<< items1[6] << ' ' << items2[6] << ' ' 
			<< stoi(items1[5]) + stoi(items2[5]) << endl;

	
	}


	return 0;
}
