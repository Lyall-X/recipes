#include <array>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <optional>
#include <string>
#include <utility>

const std::pair<bool, int> CheckPair() noexcept
{
    return {true, 42};
}

std::optional<int> CheckOptional(bool have) noexcept
{
    if (have)
        return 42;
    else
        return std::nullopt;
}

void InitList(std::initializer_list<int> list)
{
    for (const auto& value : list)
    {
        printf("%d\n", value);
    }
}

// copy-and-swap idiom
// Rule of Five: destructor, copy constructor, copy assignment operator, move constructor, move assignment operator
class CopyAndSwap
{
 public:
    CopyAndSwap() = default;
#if 0
    CopyAndSwap& operator=(const CopyAndSwap& rhs)
    {
        // step1: check self
        if (this == &rhs)
            return *this;
        // step2: release self memeory
        delete[] data_;
        data_ = nullptr;
        // step3: copy rhs to self
        data_ = new char[rhs.size_];
        size_ = rhs.size_;
        for (std::size_t i = 0; i < size_; ++i)
        {
            data_[i] = rhs.data_[i];
        }
        // step4: return self
        return *this;
    }
#endif
    CopyAndSwap(const CopyAndSwap& rhs)
    {
        size_ = rhs.size_;
        data_ = new char[size_];
        for (std::size_t i = 0; i < size_; ++i)
        {
            data_[i] = rhs.data_[i];
        }
    }

    CopyAndSwap& operator=(const CopyAndSwap& rhs) noexcept
    {
        if (this == &rhs)
            return *this;
        CopyAndSwap temp{rhs};
        swap(temp);
        return *this;
    }

    CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
    {
        swap(rhs);
        return *this;
    }

    const std::string& GetSize() const
    {
        return const_test;
    }

    std::string& GetSize()
    {
        // just for test
        return const_cast<std::string&>(std::as_const(*this).GetSize());
    }

 public:
    void swap(CopyAndSwap& rhs)
    {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
    }

 private:
    char* data_{nullptr};
    std::size_t size_{10};
    std::string const_test;
};

// RVO: return lvalue
CopyAndSwap CreateCopyAndSwap()
{
    CopyAndSwap cas;
    return cas;
}

class Point
{
 public:
    bool operator==(const Point& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    int x, y;
};

namespace std {
template <>
struct hash<Point>
{
    std::size_t operator()(const Point& p) const
    {
        return std::hash<int>{}(p.x) ^ std::hash<int>{}(p.y);
    }
};
}  // namespace std

int main()
{
    float a{};                                    // 统一初始化器
    [[maybe_unused]] int b{static_cast<int>(a)};  // 优雅的类型转换
    [[maybe_unused]] int arr[1]{};
    std::array arrstl{1, 2, 3};
    std::printf("%zu, %lu, %zu\n", std::size(arr), sizeof(arr) / sizeof(arr[0]), std::size(arrstl));  // 0

    std::pair p = CheckPair();
    printf("%d, %d\n", p.first, p.second);  // 1, 42

    std::optional opt = CheckOptional(true);
    printf("%d\n", *opt);  // 42
    opt = CheckOptional(false);
    printf("%d\n", *opt);  // 0

    // for (std::array arr{1, 2, 3, 4, 5}; const auto& value : arr)
    // {
    //     printf("%d\n", value);  // 1, 2, 3, 4, 5
    // }

    // InitList({1, 2, 3, 4, 5});  // 1, 2, 3, 4, 5
    [[maybe_unused]] CopyAndSwap swap = CreateCopyAndSwap();
    return 0;
}