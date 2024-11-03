#include <dlfcn.h>

#include <chrono>
#include <cstdio>
#include <functional>
#include <thread>

int main()
{
    printf("begin\n");
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        printf("Loop in main...\n");
        void *handle = dlopen("./libbug.so", RTLD_NOW);
        if (handle == nullptr)
        {
            printf("waitting\n");
            continue;
        }
        std::function<void()> enter_func = (void (*)())dlsym(handle, "_Z5Enterv");
        if (!enter_func)
        {
            printf("Failed to get Enter function\n");
            break;
        }
        enter_func();
    }
    printf("end\n");
    return 0;
}