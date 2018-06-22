// out.h

namespace Outer { // 命名空间Outer的定义

       int i; // 命名空间Outer的成员i的内部定义

       namespace Inner { // 子命名空间Inner的内部定义
              void f() { i++; } // 命名空间Inner的成员f()的内部定义，其中的i为Outer::i

              int i;

              void g() { i++; } // 命名空间Inner的成员g()的内部定义，其中的i为Inner::i
              void h(); // 命名空间Inner的成员h()的声明

       }

       void f(); // 命名空间Outer的成员f()的声明

       // namespace Inner2; // 错误，不能声明子命名空间
}

void Outer::f() {i--;} // 命名空间Outer的成员f()的外部定义

void Outer::Inner::h() {i--;} // 命名空间Inner的成员h()的外部定义

// namespace Outer::Inner2 {/*……*/} // 错误，不能在外部定义子命名空间
