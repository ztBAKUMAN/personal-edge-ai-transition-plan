#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

class EpollReactor {
public:
    EpollReactor() {
        epfd_ = epoll_create1(0);
        if (epfd_ < 0) perror("epoll_create1");
    }
    ~EpollReactor() { close(epfd_); }

    void addFd(int fd, uint32_t events) {
        epoll_event ev;
        ev.events = events;
        ev.data.fd = fd;
        epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev);
    }

    void run() {
        epoll_event events[16];
        int nfds = epoll_wait(epfd_, events, 16, 1000);
        std::cout << "epoll_wait returned " << nfds << " events\n";
    }

private:
    int epfd_;
};

int main() {
    EpollReactor reactor;
    reactor.addFd(STDIN_FILENO, EPOLLIN);
    std::cout << "Reactor listening on stdin...\n";
    reactor.run();
    return 0;
}
