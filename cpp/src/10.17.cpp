#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<stdlib.h>

using namespace std;

int main(int argc, char **argv){
	if (argc != 3){
		throw runtime_error("need 3 arguments");
		return -1;
	}
	map<string, string> trans_map;
	string key,value,line;
	ifstream f;
	istringstream stream;

	f.open(argv[1],ifstream::in);
	if (!f.good()){
		throw runtime_error("file cannot open " + string(argv[1]));
	}
	while (f >> key >> value){
		trans_map.insert(make_pair(key, value));
	}
	map<string,string>::iterator iter = trans_map.begin();
	while(iter!= trans_map.end()){
		cout<<"key: "<<iter->first<<" value: "<<iter->second<<endl;
		++iter;
	}
	return -1;
	f.close();
	f.open(argv[2]);
	if (!f.good()){
		throw runtime_error("file cannot open " + string(argv[2]));
	}
	while (getline(f, line)){
		cout<<"line : "<<line<<endl;
		stream.str(line);
		cout<<"stream content:"<<stream.str()<<endl;
		bool firstWord = true;
		string tmpWord;
		while (stream >> tmpWord){
			// cout<<"tmpWord: " <<tmpWord<<endl;
			map<string, string>::const_iterator iter = trans_map.find(tmpWord);
			if (iter != trans_map.end()){
				tmpWord = iter->second;
			}

			if (firstWord)
				firstWord = false;
			else
				cout << " ";
			cout<<tmpWord;
		}
		stream.clear();//如果用同一个istringstream且没有加上这句，最后stream.str(line)只是改变了底层的缓冲区，指针并没有改变，所以第二行的stream>>tmpWord就没有东西
		cout << endl;
	}
	f.close();
	return 0;
}