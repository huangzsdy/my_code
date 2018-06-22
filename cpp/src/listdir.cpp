#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
char *filename[10000];
int trave_dir(char* path, int depth)
{
    int len = 0;
    DIR *d;//声明一个句柄
    struct dirent *file;//readdir函数的返回值就存放在这个结构体中
    struct stat sb;   
   
    if(!(d = opendir(path)))
    {
        printf("error opendir %s!!!\n",path);
        return -1;
    }
    while((file = readdir(d)) != NULL)
    {
       //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;
        filename[len] = new char[256];
        strcpy(filename[len++], file->d_name);//保存遍历到的文件名
       //判断该文件是否是目录，及是否已搜索了三层，这里我定义只搜索了三层目录，太深就不搜了，省得搜出太多文件
        if(stat(file->d_name, &sb) >= 0 && S_ISDIR(sb.st_mode) && depth <= 1)
        {
            trave_dir(file->d_name, depth + 1);
        }
    }
    closedir(d);
    return len;
}
int main()
{
    int depth = 1;
    int i;
    int len = trave_dir("/home/safe_data_dir_2/yunclean/1", depth);
    for(i = 0; i < len; i++)
    {
        printf("%s\n", filename[i]);
    }
    return 0;
} 
