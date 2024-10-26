/**
 * @brief
 * 1.类型与对象
 * Param{} 比 Param() 更加安全，因为后者可能被解释为函数声明: 统一初始化语法（包含函数对象）
 * 递归过程中, 右值引用可以作为中间结果进行修改
 */
#include <cstdio>
#include <iostream>
#include <vector>
struct Param
{
    Param() { printf("Param()\n"); }
    Param(const Param &p)
    {
        (void)p;
        printf("Param(const Param &p)\n");
    }
    Param(Param &&p)
    {
        (void)p;
        printf("Param(Param &&p)\n");
    }
};

void f(Param &p)
{
    (void)p;
    printf("f(Param &p)\n");
}

void f(const Param &p)
{
    (void)p;
    printf("f(const Param &p)\n");
}

void f(Param &&p)
{
    (void)p;
    printf("f(Param &&p)\n");
}

template <typename T>
void f(T &&t)
{
    (void)t;
    printf("f(T &&t)\n");
}

// decltype: 获取值类型： 1.不带括号，获取定义时类型 2.带括号，获取作为参数的类型
// 推到函数返回值: 需要实例化出对象, decltype(f(Param{}))
#include <functional>
#include <typeinfo>
// 推到函数返回值
// declvalue: 由类型推导出对象: 1.不需要实例化 2.不受构造函数限制
template <typename F, typename... Args>
using FuncResultType = decltype(F{}(Args{}...));

template <typename F, typename... Args>
using FuncResultType2 = decltype(std::declval<F>()(std::declval<Args>()...));

// 值语义多态: std::variant, std::visit -> 双重派发技术
#include <variant>
struct VarA
{
    void Print() { printf("VarA\n"); }
};

struct VarB
{
    void Print() { printf("VarB\n"); }
};

// 打印模板类型: 1.利用警告打印  2.利用模板函数名打印
// template <typename... Ts>
// struct [[deprecated]] dump
// {};

template <typename... Ts>
void dump()
{
    printf("T: %s\n", __PRETTY_FUNCTION__);
};

#if 1
int main()
{
    // && > const &
    f(Param{});
    Param p;
    // & > const &
    f(p);
    // lambda默认为 constexpr
    constexpr auto add = [](int a, int b) { return a + b; };
    printf("add: %d\n", add(1, 2));
    // 泛型lambda
    auto add2 = [](auto a, auto b) { return a + b; };
    auto add3 = []<typename T>(T a, T b) { return a + b; };
    // bind
    int value = 1;
    std::bind(add, std::ref(value), 2);

    using Var = std::variant<VarA, VarB>;
    Var a     = VarA{};
    Var b     = VarB{};
    std::visit([](auto &&v) { v.Print(); }, a);
    std::visit([](auto &&v) { v.Print(); }, b);

    // 打印模板类型
    // dump<int, VarA, VarB> d;
    dump<Var, int>();

    return 0;
}
#endif

// ####################################################################################

#if 0
int main()
{
    return 0;
}
#endif
