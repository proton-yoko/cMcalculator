#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
int main(int argc, char **argv)
{
	if(argc != 2){
		cout << "the usage of this program is like './a.out input.txt (>> output.txt)'" << endl;
		exit(1);
	}

	//ファイル名をここで指定していたときの名残
	//string file_name = "HG00512/HG00512_chr22.txt";
	//ifstream file(file_name.c_str());
	
	ifstream file(argv[1], ios::in);
	if(!file){
		cerr << "Unable to open" << argv[1] << endl;
		exit(1);
	}	

	string line;
	string tmp;

	//vector<string> items;
	while (getline(file, line)){
		if(line[0]=='#'){
			cout << line << endl;
			continue;
		}
		vector<string> items;
		istringstream stream(line);
		while(getline(stream, tmp, ' ')){
			items.push_back(tmp);
		}


		if(items[6].substr(0,3).compare("0|0")==0){
			cout << items[0] << ' ' << items[1] << ' ' << items[2] << ' ' << items[3] << ' ' << items[4] << ' ' 
			<< items[6].substr(0,3) << ' ' << items[3] << ' ' << items[3] << ' ' << 0 << endl;
		}else if(items[6].substr(0,3).compare("0|1")==0){
			cout << items[0] << ' ' << items[1] << ' ' << items[2] << ' ' << items[3] << ' ' << items[4] << ' ' 
			<< items[6].substr(0,3) << ' ' << items[3] << ' ' << items[4] << ' ' << 1 << endl;
		}else if(items[6].substr(0,3).compare("1|0")==0){
			cout << items[0] << ' ' << items[1] << ' ' << items[2] << ' ' << items[3] << ' ' << items[4] << ' ' 
			<< items[6].substr(0,3) << ' ' << items[4] << ' ' << items[3] << ' ' << 1 << endl;
		}else if(items[6].substr(0,3).compare("1|1")==0){
			cout << items[0] << ' ' << items[1] << ' ' << items[2] << ' ' << items[3] << ' ' << items[4] << ' ' 
			<< items[6].substr(0,3) << ' ' << items[4] << ' ' << items[4] << ' ' << 2 << endl;
		}else{
			cout << "error!!!" << endl;
		}

	}


	return 0;
}
