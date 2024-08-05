#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void SocketThread(std::string str)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(8080);
    connect(fd, (sockaddr*)&addr, sizeof(addr));

    char buffer[1024];
    memccpy(buffer, str.c_str(), 0, str.length());
    int times = 1;
    while (true)
    {
        times--;
        if (times < 0)
        {
            break;
        }
        send(fd, buffer, sizeof(buffer), 0);
    }
}
int main()
{
    std::vector<std::thread> vec;
    for (int i = 0; i < 1; ++i)
    {
        vec.push_back(std::thread(SocketThread, std::to_string(2)));
    }
    for (auto& t : vec)
    {
        t.join();
    }
    return 0;
}