#include <atomic>
#include <barrier>
#include <chrono>
#include <future>
#include <latch>
#include <memory>
#include <mutex>
#include <semaphore>
#include <stop_token>
#include <thread>

/*
thread_local 需要在全局范围初始化，这样子线程才能正确获得副本，不然会出现未定义行为
thread线程在构建完成就立马执行了，但是什么时候准备好不一定, async可以选择在get的时候执行
std::atomic_flag 自旋锁等待时cpu 100%, 用完锁需要clear
timed_mutex: 在一定时间内加锁，不是自旋的
*/

int count = 0;

std::mutex m;

std::once_flag flag;
std::condition_variable c;

std::counting_semaphore s{2};

void Compete()
{
    printf("finish\n");
};
void Counter()
{
    printf("ready\n");
    s.acquire();
    printf("start\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    s.release();
    printf("end\n");
};

void Thread()
{
    Counter();
};

struct A
{
    constexpr A(){};
    int a;
};

consteval int test(int num)
{
    A* a = new A();
    a->a = num;
    delete a;
    return num;
};
int main()
{
    constexpr int a = test(1);
    static_assert(a == 1);
    // std::jthread t1(Counter);
    // std::jthread t2(Counter);
    // std::jthread t3(Counter);

    // printf("this is main\n");
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
};