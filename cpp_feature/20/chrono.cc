#include <chrono>
#include <iostream>
#include <ratio>

int main()
{
    using r1 = std::ratio<1, 60>;
    printf("r1: %lu/%lu\n", r1::num, r1::den);
    return 0;
}