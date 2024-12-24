#include "readerwriterqueue.h"

#include <iostream>
#include <thread>

#include "userqueue.h"

int main()
{
#if 0
    moodycamel::ReaderWriterQueue<int> q(100);
    while (1)
    {
        int value;
        q.try_dequeue(value);
        std::cout << value << std::endl;
        q.enqueue(1);
    }
#endif
    UserQueue<int> q;
    q.enqueue(1);
    auto out = q.dequeue();
    std::cout << out << std::endl;
    return 0;
}