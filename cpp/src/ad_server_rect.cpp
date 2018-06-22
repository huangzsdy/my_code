#include <iostream>
#include <opencv2/opencv.hpp>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "detect.h"
#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <locale>


using namespace std;
using namespace cv;
using namespace boost::property_tree;


extern void init();
vector<pair<cv::RotatedRect, wstring>> detect2(const Mat& src);
extern void close();

const int BUF_SIZE = 40960;
const int CHUNK_SIZE = 256;

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "args: [ip] [port]" << endl;
		return 1;
	}

	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	int enable = 1;
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  //具体的IP地址
	serv_addr.sin_port = htons(atoi(argv[2]));  //端口
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	init();

	listen(serv_sock, 20);
	std::cout << "load model" << endl;

	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	char buffer[BUF_SIZE] = {0};
	char chunk[CHUNK_SIZE] = {0};
	char *not_exists_err = "not exists";
	char *illegal_format_err = "illegal format";
	while (1) {
		int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		try {
			while (read(clnt_sock, chunk, CHUNK_SIZE-1) > 0) {
				std::cout << "chunk" << chunk << endl;
				strcat(buffer, chunk);
				std::cout<<"received data"<<endl;
			}
			std::cout<<"buffer is: "<<buffer<<endl;
			if (access(buffer, F_OK) != 0) {
				write(clnt_sock, not_exists_err, strlen(not_exists_err));
			    std::cout<<"can't read picture:"<<buffer<<endl;}
			else {
				cv::Mat image = cv::imread(buffer);
				cv::Size image_size = image.size();
				// 去掉右下角的水印（QQ空间）
				// 先取出右下角区域
				int roi_width = 250, roi_height = 100;
				int roi_x = image_size.width - roi_width;
				int roi_y = image_size.height - roi_height;
				if (roi_x < 0) {
					roi_x = 0;
					roi_width = image_size.width;
				}
				if (roi_y < 0) {
					roi_y = 0;
					roi_height = image_size.height;
				}
				cv::Rect roi(roi_x, roi_y, roi_width, roi_height);
				// 然后把右下角区域赋值成0
				image(roi).setTo(0);

				vector<pair<cv::RotatedRect, wstring>> result = detect2(image);
				
				ptree tree;
				if(result.size() > 0){
					ptree rects;
					for(int i = 0;i<result.size();i++){
						wstring tmpWord = result[i].second;
						cv::RotatedRect detectRect = result[i].first;
						//接下来把wstring 转换成string
						ptree child;
						unsigned int len = tmpWord.size() * 4;
						setlocale(LC_CTYPE, "");
						char *p= new char[len];
						wcstombs(p,tmpWord.c_str(),len);
						string word(p);
						delete p;

						child.put("word",word);
						float w = detectRect.size.width;
						float h = detectRect.size.height;
						float x = detectRect.center.x;
						float y = detectRect.center.y;
						float angle = detectRect.angle;

						child.put<float>("w",w);
						child.put<float>("h",h);
						child.put<float>("x",x);
						child.put<float>("y",y);
						child.put<float>("angle",angle);
						rects.push_back(make_pair("",child));
					}
					tree.put_child("rects",rects);
				}
				
				stringstream  os;
				write_json(os,tree);
				sprintf(buffer, "%s", os.str().c_str());
				write(clnt_sock,buffer,strlen(buffer));
			}
		}
		catch (...) {
			write(clnt_sock, illegal_format_err, strlen(illegal_format_err));
		}

		close(clnt_sock);
		std::cout<<"close sock"<<endl;
		memset(buffer, 0, BUF_SIZE);
		memset(chunk, 0, CHUNK_SIZE);
	}
	close();

	return 0;
}
