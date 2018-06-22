#include <iostream>
#include <opencv2/opencv.hpp>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "libzbar.h"
using namespace std;
using namespace cv;
const int BUF_SIZE = 1024;
const int CHUNK_SIZE = 1024;
const char * host = "0.0.0.0";

int detect(const char * path,char *message)
{ 
	if(access(path, F_OK ) != 0)
	{
		return -2;
	}
	TBitmap bitmap;
	IplImage *ori = cvLoadImage(path,1);
	if (!ori || ori == NULL|| !ori->imageData||ori->imageData==NULL) {
		return -1;
	}
	int height = ori->height;
	int width  = ori->width;
	int channels = ori->nChannels;

	CvSize size_enlarge = cvSize(cvRound(1*width), cvRound(1*height));
	IplImage * img = cvCreateImage(size_enlarge,IPL_DEPTH_8U,3);
	cvResize(ori,img,CV_INTER_CUBIC);
//	cvSaveImage("crop.jpg",img);
//exit(1);
	TPixelMode mode;
	// unsigned char*  buffer = image.data;
	int i, j;
	int pitch = (width*24+31)/32*4;
	unsigned char* buffer = (unsigned char*)malloc(height*pitch);
	unsigned char* ptrsrc = (unsigned char*)img->imageData;
	unsigned char* ptrdst = buffer;
	for(i = 0; i < height; ++i) {
		memcpy(ptrdst, ptrsrc, width*3);
		ptrsrc += img->widthStep;
		ptrdst += pitch;
	}
	mode = gr_pixel_mode_rgb24;
	bitmap.height = height;
	bitmap.width  = width;
	bitmap.xdpi   = 96;
	bitmap.ydpi   = 96;
	bitmap.mode   = mode;
	bitmap.pitch  = pitch; 
	bitmap.grays  = 0;
	bitmap.buffer = buffer;
	printf("width: %d,height:%d,channel:%d\n,pitch:%d\n",img->width,img->height,channels,pitch);

	TStatus nStatus;
	TZBarDecode * stDecodeRest = (TZBarDecode *)malloc(sizeof(TZBarDecode) * 32);

	TDecodeHintType stDecodeHint;

	stDecodeHint.bTryHarder              = 1;
	stDecodeHint.bPureBarcode            = 0;
	stDecodeHint.bMultiBarcode           = -1;
	stDecodeHint.bAssumeCode39ChechDigit = 0;
	stDecodeHint.bNeedResultPoint        = 1;
	stDecodeHint.naFormats[0]            = CODE_25;
	stDecodeHint.naFormats[1] = MATRIX_25;
	stDecodeHint.naFormats[2] = ITF;
	stDecodeHint.naFormats[3] = CODABAR;
	stDecodeHint.naFormats[4] = RSS_14;
	stDecodeHint.naFormats[5] = RSS_EXPANDED;
	stDecodeHint.naFormats[6] = UPC_EAN_EXTENSION;
	stDecodeHint.naFormats[7] = UPC_E;
	stDecodeHint.naFormats[8] = UPC_A;
	stDecodeHint.naFormats[9] = CODE_39;
	stDecodeHint.naFormats[10] = CODE_93;
	stDecodeHint.naFormats[11] = CODE_128;
	stDecodeHint.naFormats[12] = EAN_8;
	stDecodeHint.naFormats[13] = EAN_13;
	stDecodeHint.nFormatSize = 14;
	stDecodeHint.nCharset                = -1; //如果不知道一定要设置-1
	
	memset(stDecodeRest, 0, sizeof(TZBarDecode)*32);
 	nStatus = ZBar_Decode(&bitmap, &stDecodeHint, stDecodeRest, 32);
 	cvReleaseImage(&img);
 	cvReleaseImage(&ori);
	if (nStatus > 0)
	{
		TRect locate[nStatus];

		for (int i = 0; i < nStatus; ++i)
		{
			locate[i] = stDecodeRest[i].rectBar;
			sprintf(message,"number:%d#location%d:{left:%d,right:%d,top:%d,bottom:%d}",nStatus,i+1,locate[i].nLft,locate[i].nRgt,locate[i].nRgt,locate[i].nTop,locate[i].nBtm);
		}
	}
	else
	{
		sprintf(message,"number:%d",nStatus);
	}
	if(stDecodeRest != NULL)
	{
		free(stDecodeRest);
		stDecodeRest = NULL;
	}
	if(buffer != NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	return nStatus;
}


int main(int argc, char** argv) {
	const char * port = argv[1];
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(host);  //具体的IP地址
	serv_addr.sin_port = htons(atoi(port));  //端口
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(serv_sock, 20);
	struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char buffer[BUF_SIZE] = {0};
    char chunk[CHUNK_SIZE] = {0};
    printf("beging to listen [host]: %s [port]: %s\n",host,port);
    printf("0\n");
    while (1) {
    	char * message;
    	try {
    		int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	    	if (clnt_sock == -1)
	    	{
	    		 printf("socket wrong\n");
	    		 continue;
	    	}
	    	signal(SIGPIPE, SIG_IGN);
	    	// printf("2\n");
    		// printf("3\n");
	    	if (read(clnt_sock, chunk, CHUNK_SIZE-1) > 0) {
	    		printf("receive data\n");
	    		strcat(buffer, chunk);

	    	}
	    	printf("%s\n", buffer);
	    	clock_t start=clock();
	    	message = new char[1000];
	    	// printf("4\n");
	    	int nStatus = detect(buffer,message);
	    	// printf("5\n");
	    	clock_t finish=clock();
	    	double totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	    	char reBuf[BUF_SIZE] = {0};
	    	if(nStatus == -2)
	    	{
	    		char  wrong[256] = "wrong:file not exists";
	    		sprintf(reBuf, "%s#final_time:%lf",wrong,totaltime);
	    		printf("reBuf:%s\n",reBuf);
	    		write(clnt_sock, reBuf, 1024);
	    		close(clnt_sock);
	    	}
	    	else if(nStatus == -1){
	    		char wrong [256] = "wrong:could not open the file";
	    		sprintf(reBuf, "%s#final_time:%lf",wrong,totaltime);
	    		printf("reBuf:%s\n",reBuf);
	    		write(clnt_sock, reBuf, 1024);
	    		close(clnt_sock);
	    	}
	    	else {
	    		sprintf(reBuf, "%s#final_time:%lf",message,totaltime);
	    		printf("reBuf:%s\n",reBuf);
	    		write(clnt_sock, reBuf, 1024);
	    		close(clnt_sock);
	    	}
    	} 
    	catch (const char* msg) {
    		printf("%s\n",msg );
    	} 
    	catch (...) {
    		printf("Internal error\n");
    	}
    	if (message != NULL)
    	{
    		delete [] message;
    		message = NULL;
    	}
    	memset(buffer, 0, BUF_SIZE);
    	memset(chunk, 0, CHUNK_SIZE);
    }
    cout << "finish to listen"<<endl;
	return 0;
}
