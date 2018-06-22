#include<iostream>
#include<sstream>

using namespace std;

int main(int argc,char **argv){
	istringstream stream;
	char * tmp[2] = {"h b","w c"};
	for(int i=0;i<2;i++){
		stream.str(tmp[i]);
		cout<<"stream content: "<<stream.str()<<endl;
		string word;
		while(stream>>word){
			cout<<"word: "<<word<<" ";
//			stream.clear();
		}
		stream.clear();
		cout<<endl;
	}
	return 0;
}
