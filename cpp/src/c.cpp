#include <iostream>
#include <string>
#include <list>

using namespace std;
typedef list<string> Strlist;

int main(int argc, char ** agrv)
{
    Strlist test;
    test.push_back("middle");
    test.push_back("back");
    test.push_front("front");
    cout << test.front() << endl;
    cout << *test.begin() << endl;
    //test.pop_front();
    //test.pop_back();
    //test.remove("middle");
    cout << test.front() << endl;
    cout << test.back() << endl;
    cout << "---------------------" << endl;
    Strlist test2;
    Strlist::iterator it = test.begin();
    Strlist::reverse_iterator rit = test.rbegin();
    //while (test.empty() != true)
    //{
    //  cout << test.front() << endl;
    //  test.pop_front();
    //}
    test2.push_back("aa");
    test2.push_back("bb");
    test2.push_back("cc");
    test.swap(test2);
    test.sort();
    cout<<test.size()<<endl;
    for (; rit != test.rend(); rit++)
         cout << *rit << endl;
    for (; it != test.end(); it++)
         cout << *it << endl;
}
