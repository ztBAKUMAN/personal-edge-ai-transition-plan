#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>

int main() {
    int epfd = epoll_create1(0);
    if (epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    // Non-blocking I/O readiness notification
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0) {
        perror("epoll_ctl");
    }

    std::cout << "epoll created fd=" << epfd
              << ", monitoring stdin for input\n";
    close(epfd);
    return 0;
}
