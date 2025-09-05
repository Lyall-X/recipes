#include <cassert>
#include <cstdio>
#include <thread>

template <typename T>
class DebufSharedPtrCounterType
{
 public:
    DebufSharedPtrCounterType(T count) noexcept : count_(count) {}
    // 支持显示/隐式类型转换为 long
    operator long() const
    {
        Check();
        return static_cast<long>(count_);
    }
    DebufSharedPtrCounterType<T>& operator=(T count)
    {
        count_ = count;
        return *this;
    }
    // 前置自增，返回引用
    DebufSharedPtrCounterType<T>& operator++()
    {
        Check();
        ++count_;
        return *this;
    }
    // 后置自增，参数必须int，返回拷贝
    DebufSharedPtrCounterType<T> operator++(int)
    {
        Check();
        DebufSharedPtrCounterType<T> temp = count_;
        ++count_;
        return temp;
    }

    DebufSharedPtrCounterType<T>& operator--()
    {
        Check();
        --count_;
        return *this;
    }

    DebufSharedPtrCounterType<T> operator--(int)
    {
        Check();
        DebufSharedPtrCounterType<T> temp = count_;
        --count_;
        return temp;
    }

 private:
    void Check() const
    {
        if (id_ != std::this_thread::get_id()) [[unlikely]]
        {
            assert(false && "DebufSharedPtrCounterType used from multiple threads");
        }
    }

 private:
    T count_{};
    std::thread::id id_ = std::this_thread::get_id();
};