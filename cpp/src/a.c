// #include <stdio.h>
// #include <stdlib.h>
// #include "cJSON.h"

// int main(int argc,char **argv){
//     cJSON *root;
//     root = cJSON_CreateObject();
//     cJSON * object_body;
//     char * body = "rects";
//     cJSON_AddItemToObject(root,body,object_body=cJSON_CreateObject());
//     cJSON_AddNumberToObject(object_body,"h",102);
//     cJSON_AddNumberToObject(object_body,"w",90);
//     char * s = cJSON_Print(root);
//     if (s) {
//         DEBUG("json is %s",s);
//         free(s);
//     }
//     cJSON_Delete(root);
// }

#include<iostream> 
#include<algorithm>
#include<string>


using namespace std;

int main()
{   
    //char * tmp = "hello123";
    //char tmp2[] = "hello";
    //cout << *tmp << endl;
    //cout << sizeof(tmp)<<endl;
    //cout << sizeof(*tmp)<<endl;
    //cout << sizeof(tmp2) << endl;
    //cout << sizeof(*tmp2) << endl;
    //cout << tmp2;
    //cout << tmp << endl;
    //string s2 = string(tmp2);
    //cout << s2.size();
    char *p = new char('a');
    //cout << p << endl;
    delete p;
    p = 0;
    if (p == NULL){
        cerr << "sth error" << endl;
        throw runtime_error("p 是空指针");
    }
    return 0;
}
