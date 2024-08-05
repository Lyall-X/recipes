#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <thread>

int main()
{
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 1024);

    int epoll_fd = epoll_create1(0);
    struct epoll_event ev;
    ev.events  = EPOLLIN;
    ev.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);

    struct epoll_event events[1024];
    while (true)
    {
        int nfds = epoll_wait(epoll_fd, events, 1024, 5000);
        for (int i = 0; i < nfds; ++i)
        {
            int fd = events[i].data.fd;
            if (fd == listen_fd)
            {
                std::cout << "accept" << std::endl;
                int conn_fd = accept(listen_fd, nullptr, nullptr);
                ev.events   = EPOLLIN;
                ev.data.fd  = conn_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev);
            }
            else
            {
                char buf[1024];
                int n = recv(fd, buf, sizeof(buf), 0);
                if (n == 0)
                {
                    std::cout << "fd:" << fd << " closed" << std::endl;
                    shutdown(fd, SHUT_RDWR);
                    close(fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
                }
                else if (n < 0)
                {
                    std::cout << "fd:" << fd << " recv error" << std::endl;
                    shutdown(fd, SHUT_RDWR);
                    close(fd);
                }
                else
                {
                    std::cout << "fd:" << fd << " recv:" << buf << std::endl;
                }
            }
        }
    }

    return 0;
}
