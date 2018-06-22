#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class T,class D>
class Member
{
public:
    Member(T t, D d):name(t), sal(d) {}
    void print();
private:
    T name;
    D sal;
};

template<class T,class D>
void Member::print()
{
    cout << name << " " << sal << endl;
}

int main()
{
    typedef Member<string, double> M;
    vector<M> v;
    v.push_back(M("Robert", 333));
    v.push_back(M("Linda", 222));
    vector<M>::iterator It = v.begin();
    cout << "Entire vector:" << endl;
    while (It != v.end())
        (It++)->print();
    cout << endl;
    cout << "Return from back()" << endl;
    v.back().print();//vector 的begin 和end 返回迭代器，可以当成指针，front 和back 返回该变量的引用
}
