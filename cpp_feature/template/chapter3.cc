#include <cstdio>
#include <cstdlib>

// ################## 1. concept ##################
#include <type_traits>
template <typename T>
concept integral = std::is_integral_v<T>;

// 合取与析取
template <typename T>
concept integral_and_rvalue = std::is_integral_v<T> || std::is_rvalue_reference_v<T>;

// 可变参数
struct TestA
{
    using type = int;
};
struct TestB
{};

struct TestC
{
    using type = int[];
};

// 1. type 必须， integral 可选
template <typename... Ts>
concept have_type_and_integral = (std::is_integral_v<typename Ts::type> || ...);

// 2. type可选，通过延迟特化
template <typename T>
concept has_value = std::is_integral_v<typename T::type>;
template <typename... Ts>
concept have_type_and_integral2 = (has_value<Ts> || ...);

// 3. () 具有原子性
template <typename T, typename U>
concept concept_test1 = std::is_integral_v<typename T::type> || std::is_floating_point_v<typename U::type>;
template <typename T, typename U>
concept concept_test2 = (std::is_integral_v<typename T::type> || std::is_floating_point_v<typename U::type>);

// 4. ! 否定操作
template <typename T>
concept concept_test3 = std::is_integral_v<typename T::type>;
template <typename T>
concept concept_test4 = !std::is_integral_v<typename T::type>;  // T: 拥有 type 成员，但是不是 integral
template <typename T>
concept concept_test5 = !concept_test3<T>;  // T: 不拥有 type 成员，或不是 integral

// ################## 2. require表达式 ##################

int main()
{
    // 只能用于 1.非上下文求值 2.bool返回
    static_assert(integral<int>);
    static_assert(integral_and_rvalue<int&&>);

    static_assert(have_type_and_integral<TestA>);          // type 必须， integral 可选
    static_assert(have_type_and_integral2<TestA, TestB>);  // type, integral 同时满足即可

    static_assert(concept_test1<TestA, TestB>);
    // static_assert(concept_test2<TestB, TestB>); // TestB 不满足

    static_assert(concept_test3<TestA>);
    static_assert(concept_test4<TestC>);
    static_assert(concept_test5<TestB>);
    return 0;
}