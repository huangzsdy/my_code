#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include<algorithm>

using namespace std;

#define SERVPORT 22225
#define MAXDATASIZE 1024
#define SERVER_IP "127.0.0.1"
#define DATA "./images/2.jpg"



vector<string> getfiles(const string& dir, const string& extension, bool withpath){
  vector<string> filenames;
  DIR *pDIR;
  struct dirent *entry;
  string filename;
  if( pDIR=opendir(dir.c_str()) ){
    while(entry = readdir(pDIR)){
      filename = entry->d_name;
      if (filename.substr(filename.find_last_of(".") + 1) == extension){
        if (withpath){
          filenames.push_back(dir + "/" + filename);
 	      }
        else
          filenames.push_back(filename);
      }
    }
    closedir(pDIR);
  }
  sort(filenames.begin(), filenames.end());
  return filenames;
}

int main(int argc, char* argv[]) {
    int sockfd, recvbytes;
    char buf[MAXDATASIZE];
    struct hostent *host;
    struct sockaddr_in serv_addr;
      
    string folderName = "/home/faceall/huangzesang/qr0504/Label_pic";
    char* folders[2] = {"/home/faceall/huangzesang/qr0504/Label_pic","/home/faceall/huangzesang/qr0504/pdf_imgs"};
    //char * folders[2] = {".","/home/faceall/huangzesang/qr-code/pic/"};
    // char * folder ="/home/faceall/huangzesang/qr-code/20160325/yiweima"};"/home/faceall/huangzesang/qingyun_test/qr_test",
    for(int i=0;i<2;i++){
      char * extension = NULL;
      if(i==0)
        //extension = "JPG";
        continue;
      else
        extension = "jpg";
      vector<string>filenames = getfiles(string(folders[i]),extension,true);
      for(int i=0;i<filenames.size();i++){
          if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket error!");
            exit(1);
          }
          bzero(&serv_addr,sizeof(serv_addr));
          serv_addr.sin_family    = AF_INET;
          serv_addr.sin_port      = htons(SERVPORT);
          serv_addr.sin_addr.s_addr= inet_addr(SERVER_IP);

          if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) {
           perror("connect error!\n");
           exit(1);
          }

          write(sockfd,filenames[i].c_str(), filenames[i].size()+1);
          // shutdown(sockfd, SHUT_RDWR);
          if((recvbytes = recv(sockfd,buf,MAXDATASIZE,0)) == -1){
            perror("recv error!\n");
            exit(1);
          }
          buf[recvbytes] = '\0';
          const char * split = ":";
          char * s = strstr(buf,split);
          printf("%s %c\n",filenames[i].substr(filenames[i].find_last_of('/')+1).c_str(),*(s+1));

          memset(buf,0,sizeof(buf));
          close(sockfd);  
        }
    }
    return 0;
}