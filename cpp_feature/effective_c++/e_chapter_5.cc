/**
std::move执行到右值的无条件的转换，但就自身而言，它不移动任何东西。
std::forward只有当它的参数被绑定到一个右值时，才将参数转换为右值。
std::move和std::forward在运行期什么也不做。

1.形参永远是左值，即使它的类型是一个右值引用
参数左值：void f(Widget&& w);
返回值右值：Widget f() { return std::move(w); }
万能引用(转发引用)：void f(T&& w);


std::move: 去除左值&符号，添加&&符号使其变成右值引用
1.不要将移动的对象设置为const，因为lvalue-reference-to-const允许被绑定到一个const右值上，移动操作会修改对象的状态，所以会隐式转化为拷贝操作
2.std::move 不移动任何东西，不保证转换的对象一定被移动
3.std::move 能保证的是，应用一个对象，得到一个右值

std::forward用法：接受一个模板T的万能引用，将参数转发给另一个函数
模板生成左值与右值的重载，但是形参永远是左值，在内部会产生左值的调用
当形参都是左值，std::forward如何知道实参的类型是左值还是右值？
    - 靠模板T
template<typename T>
void logAndProcess(T&& param)
{
    process(std::forward<T>(param));
}

*/

#include <iostream>

class MyString
{
 public:
    MyString()
    {
        std::cout << "default constructor" << std::endl;
    }

    MyString(const char* c) : MyString(std::string(c))
    {
        std::cout << "const char* constructor" << std::endl;
    }

    MyString(const std::string& str)
    {
        str_ = str;
        std::cout << "default constructor" << std::endl;
    }

    MyString(std::string&& str)
    {
        str_ = std::move(str);
        std::cout << "move constructor" << std::endl;
    }
    std::string str_;
};

void TestFunc(const MyString& str)
{
    std::cout << "const ref: " << str.str_ << std::endl;
}

void TestFunc(MyString&& str)
{
    std::cout << "rvalue: " << str.str_ << std::endl;
}

int main()
{
    // MyString str("hello");
    // TestFunc(str);  // move ctor -> const ref
    TestFunc("world");
    return 0;
}