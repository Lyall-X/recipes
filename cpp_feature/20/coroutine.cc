#include <chrono>
#include <coroutine>
#include <iostream>

struct Ret
{
    struct promise_type
    {
        std::suspend_always initial_suspend()
        {
            printf("initial_suspend\n");
            return {};
        }
        Ret get_return_object()
        {
            printf("get_return_object\n");
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always final_suspend() noexcept
        {
            printf("final_suspend\n");
            return {};
        }

        void return_void()
        {
            printf("return_void\n");
        }
        void unhandled_exception()
        {
            printf("unhandled_exception\n");
        }

        std::suspend_always yield_value(int value)
        {
            printf("yield_value: %d\n", value);
            this->value = value;
            return {};
        }
        int value = 0;
    };

    Ret(std::coroutine_handle<promise_type> coro) : coro(coro)
    {
        printf("Ret\n");
    }
    ~Ret()
    {
        printf("~Ret\n");
        coro.destroy();
    }
    std::coroutine_handle<promise_type> coro;
};

struct Awaiter
{
    bool await_ready()
    {
        printf("await_ready\n");
        return false;
    }
    void await_suspend(std::coroutine_handle<Ret::promise_type> coro)
    {
        printf("await_suspend: %d\n", coro.promise().value);
        coro();
    }
    void await_resume()
    {
        printf("await_resume\n");
    }
};

Ret foo()
{
    printf("foo begin\n");
    co_yield 100;
    co_await Awaiter{};
}

int main()
{
    auto r = foo();
    r.coro.resume();
    printf("co: %d\n", r.coro.promise().value);
    r.coro.resume();
    std::cout << std::boolalpha << r.coro.done() << std::endl;
}
