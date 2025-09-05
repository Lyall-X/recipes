#include "base/define.h"

// 变参类型
template <typename... Args>
int sumType(Args... args)
{
    (std::cout << ... << args) << std::endl;
    return (1 + ... + args);
}

// 变参值
template <int... args>
int sum()
{
    return (args + ... + 1);
}

int main()
{
    int num1 = sumType(1, 2, 3);
    int num2 = sum<1, 2, 3>();
    GDEBUG(num1);
    GDEBUG(num2);
    return 0;
}