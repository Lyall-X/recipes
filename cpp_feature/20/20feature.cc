#include <any>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std::chrono;
void duration_times()
{
    minutes m(1);
    seconds s(m);
}

int main()
{
    duration_times();
    const char *p = "1231";
    p             = "123213214";  // 修改指针指向的内容
    std::cout << p << std::endl;

    char const *p2 = "1231";
    p2             = "123213214";  // 修改指针指向的内容

    char *const p3 = new char[5];  // 指针常量，指向的内容可以修改
    *p3            = '4';          // 修改指针指向的内容
    delete[] p3;                   // 释放内存
    return 0;
}
