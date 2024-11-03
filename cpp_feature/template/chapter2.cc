#include <cstdio>
#include <cstdlib>

template <typename T>
void PT()
{
    printf("T: %s\n", __PRETTY_FUNCTION__);
}

// 1.ADL: 非限定名称查找下生效
void func(int){};
/**
1. 静态成员变量  T::value, 类型别名 typename T::value(c++20放松了限制)
2. 模板元编程 -> 优于 SFINAE
3. 函数重载不考虑返回值: 因为返回值可以不处理
4. 模板约束: 额外模板参数 enable_if_t, 返回值限定 auto xxx() -> enable_if_t<is_same_v<T, int>, int>
*/

// ################## 1. declvalue ##################
// 右值引用只涉及类型引用的绑定，并不实际创建对象
#include <type_traits>
template <typename T>
T declvalue(long);  // 只有void匹配

template <typename T, typename U = T&&>
U declvalue(int);  // 非void优先匹配
// 辅助模板用于延迟触发 assert_assert, 同时避免declvalue求值
template <typename T>
struct declvalue_assist : std::false_type
{};
template <typename T>
auto declvalue() noexcept -> decltype(declvalue<T>(0))  // 可选，辅助编译器推导返回值
{
    static_assert(declvalue_assist<T>::value, "declvalue: 只能用于类型推导");
    return declvalue<T>(0);
}

// ################## 2. type traits ##################
template <typename T, typename U>
struct is_same : std::false_type  // 能匹配所有类型, false
{};
template <typename T>
struct is_same<T, T> : std::true_type  // 偏特化类型, true
{};

template <bool, typename T = void>  // T 没有使用可以缺省
struct enable_if                    // 没有type替换失败
{};

template <typename T>
struct enable_if<true, T>
{
    using type = T;  // 其实T是void，但是额外type的成员
};

// 类型自省: 结构拆分
// 1.实现通用模板，防止编译不过
template <typename T>
struct function_traits
{};
// 2.特化模板: a.函数类型 b.剖析函数结构
#include <utility>
template <typename R, typename... Args>
struct function_traits<R(Args...)>
{
    using return_type                   = R;
    using args_type                     = std::tuple<Args...>;
    static constexpr size_t num_of_args = sizeof...(Args);
    template <size_t I>
    using arg = std::tuple_element_t<I, args_type>;
};
// ################## 3. type traits ##################
// 标签分发: 函数重载
// if constexpr 判断
// template <class...> using void_t = void; 用于判断 <> 里的类型是否良构

int main()
{
    // 不采用ADL
    (func)(1);

    // declvalue 类型右值引用，返回的是value
    decltype(declvalue<int>()) a = 1;
    int&& b                      = 1;
    PT<decltype(declvalue<int>())>();    // [T = int &&] 表达式右值引用
    PT<decltype((declvalue<int>()))>();  // [T = int &&] 表达式右值引用
    PT<decltype(b)>();                   // [T = int &&] 右值
    PT<decltype((b))>();                 // [T = int &]  表达式左值

    // type traits: type check
    static_assert(std::is_integral_v<int>);
    static_assert(std::is_floating_point_v<float>);
    static_assert(std::is_same_v<int, int>);
    static_assert(!std::is_class_v<int>);
    // type traits: type transform
    static_assert(std::is_same_v<std::remove_const_t<const int>, int>);
    static_assert(std::is_same_v<std::add_const_t<int>, const int>);
    static_assert(std::is_same_v<std::remove_reference_t<int&>, int>);
    static_assert(std::is_same_v<std::remove_reference_t<int&&>, int>);
    static_assert(std::is_same_v<std::add_pointer_t<int>, int*>);
    static_assert(std::is_same_v<std::decay_t<int[10]>, int*>);
    // type traits: assist template
    using warp = std::integral_constant<int, 100>;  // type, value_type 成员
    static_assert(warp::value == 100);
    static_assert(std::is_same_v<warp::value_type, int>);
    using false_warp = std::integral_constant<bool, false>;
    static_assert(!false_warp::value);
    // 空基类优化: 继承空基类为0字节 or 组合用 [[no_unique_address]]

    return 0;
}