#include "out.h"

#include <iostream>

using namespace Outer; // 注意，此处无::Inner

using namespace std;

// using Inner::f; // 编译错误，因为函数f()有名称冲突

using Inner::g; // 此处省去Outer::，是因为Outer已经被前面的using指令作用过了
using Inner::h;

int main ( ) {

       i = 0; // Outer::i

       f(); // Outer::f()，Outer::i = -1;

       Inner::f(); // Outer::i = 0;

       Inner::i = 0;

       g(); // Inner::g()，Inner::i = 1;

       //h(); // Inner::h()，Inner::i = 0;

       cout << "Hello, World!" << endl;

       cout << "Outer::i = " << i << ",  Inner::i = " << Inner::i << endl;

}

 
