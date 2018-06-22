#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<dirent.h>
#include<stdlib.h>

using namespace std;

void readFileTree(vector<string>&fileNames,const string&dir){
	DIR * pDir = NULL;
	struct dirent * ptr;
	string basePath = dir;
	string fileName;
	if((pDir=opendir(dir.c_str()))== NULL){
		cerr<<"dir can not open "<<endl;
		exit(1);
	}

	while((ptr= readdir(pDir))!=NULL){
		if(strcmp(ptr->d_name,".")==0||strcmp(ptr->d_name,"..")==0){
			// clog<<" current dir or parent dir "<<ptr->d_name<<endl;
			continue;
		}
		else if(ptr->d_type == 8){				//file
			fileNames.push_back(basePath + "/" + string(ptr->d_name));
		}
		else if(ptr->d_type == 4){      		    //dir
			readFileTree(fileNames,basePath + "/" + string(ptr->d_name));
		}
	}
	closedir(pDir);
	return ;
}

vector<string> getFiles (const string &dir,const string &extention){
	DIR * pDir = NULL;
	struct dirent * ptr;	
	vector<string> fileNames;
	if((pDir=opendir(dir.c_str()))){
		while((ptr = readdir(pDir))){
			string fileName = ptr->d_name;
			// if(fileName.substr(fileName.find_last_of('.')+1) == extention){
			// 	fileNames.push_back(fileName);
			// }
			if(strstr(ptr->d_name,extention.c_str())){
				fileNames.push_back(fileName);
			}
		}
		closedir(pDir);
	}
	return fileNames;
	
}

int main(int argc,char **argv){
	if(argc !=2){
		cerr<<"usage: "<<argv[0]<<" imagePath"<<endl;
		return -1;
	}
	string path = argv[1];
	// vector<string> imageNames = getFiles(path,"jpg");
	vector<string> imageNames;
	readFileTree(imageNames,path);
	for(vector<string>::iterator iter = imageNames.begin();iter!= imageNames.end();iter++){
		cout<<*iter<<endl;
	}
	return 0;
}
