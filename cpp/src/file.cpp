#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

int main(int argc, char** argv){
        ifstream fp("tmp.txt");
        string tmp;
        vector<string> content;        
        while (getline(fp, tmp)){
                if (tmp.empty())
                        continue;
                cout << tmp << endl;
                content.push_back(tmp);
        }
        for(vector<string>::iterator iter = content.begin();iter != content.end();++iter){
            cout<<"line content: "<<*iter<<endl;
        }
        return 0;
}

