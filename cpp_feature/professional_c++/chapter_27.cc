#include <atomic>
#include <chrono>
#include <cstdio>
#include <exception>
#include <thread>

struct MyType1 : public std::atomic<int>
{
    int a;
    int b;
};

struct MyType2
{
    int a;
    MyType1 b;
};

int main()
{
    return 0;
}