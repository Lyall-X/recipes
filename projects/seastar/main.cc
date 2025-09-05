#include <cstdio>

#include "counter.h"
int main()
{
    DebufSharedPtrCounterType<long> c = 10;
    printf("c = %ld\nc++ = %ld\nc-- = %ld\n++c = %ld\n--c = %ld\n",
           long(c),
           long(c++),
           long(c--),
           long(++c),
           long(--c));
    return 0;
}