#include <iostream>
#include <vector>  // standard library

// noexcpt: move semantics, destructor, and simple functions
// vector push: strong exception safety guarantee
// T&& t: forwarding reference
// 移动后再次使用: valid but unspecified state, 不会成为 undefined behavior 但是不能依赖里面的数值了
// RVO and NRVO: no copy, no move, no destructor call, no memory allocation

class Test
{
 public:
    Test(int size) { data = new int[size]; }        // Regular constructor
    Test(Test &&other) noexcept : data(other.data)  // move constructor
    {
        other.data = nullptr;
    }
    Test &operator=(Test &&other) noexcept  // move assignment operator
    {
        if (this != &other)  // self-assignment check
        {
            if (data)
            {
                delete[] data;
            }
            data       = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    Test(const Test &other)            = delete;  // copy constructor
    Test &operator=(const Test &other) = delete;  // copy assignment operator

    ~Test() noexcept
    {
        if (data)
        {
            delete[] data;
            data = nullptr;
        }
    }

 private:
    int *data = nullptr;
};

int main()
{
}