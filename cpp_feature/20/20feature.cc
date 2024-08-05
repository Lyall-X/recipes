#include <any>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std::chrono;
void duration_times()
{
    minutes m(1);
    seconds s(m);
}

int main()
{
    duration_times();
    return 0;
}
