#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

vector<string> readFile(const char * filename){
	vector<string> content;
	ifstream fp(filename);
	string tmp;
/*
	while (fp >> tmp)//这是每次读一个单词，
		content.push_back(tmp);
*/
	while (getline(fp,tmp)){
		cout<<"tmp : "<<tmp<<endl;
		content.push_back(tmp);
	}
	cout<<"content length: "<<content.size()<<endl;
	return content;

}
int main(int argc, char **argv){
	string filename;
	cout << "please enter filename: " << endl;
	cin >> filename;
	fstream fp;
	fp.open("hello",fstream::in|fstream::trunc);

	vector<string> fileContent = readFile(filename.c_str());
	vector<string>::iterator iter = fileContent.begin();
	for (; iter != fileContent.end(); iter++)
		cout << *iter<<endl;
	return 0;
}