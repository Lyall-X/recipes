#include <any>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void test(std::vector<int> vec)
{
    if (vec.empty())
    {
        return;
    }

    auto rid = vec.back();
    vec.pop_back();
    printf("rid: %d\n", rid);
    auto func = [vec]() {
        printf("vec size: %lu\n", vec.size());
        test(vec);
    };
    func();
}

int main()
{
    test({1, 2, 3});
    return 0;
}
