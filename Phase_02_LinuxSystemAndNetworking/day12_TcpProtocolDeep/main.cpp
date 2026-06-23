#include <iostream>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // TCP_NODELAY: disable Nagle's algorithm
    int flag = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

    // TCP_QUICKACK: send ACK immediately (Linux 2.4.4+)
    setsockopt(fd, IPPROTO_TCP, TCP_QUICKACK, &flag, sizeof(flag));

    // SO_REUSEADDR: reuse address after TIME_WAIT
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    std::cout << "TCP options configured successfully\n";
    std::cout << "  TCP_NODELAY: disabled Nagle\n";
    std::cout << "  TCP_QUICKACK: immediate ACK\n";
    std::cout << "  SO_REUSEADDR: address reuse\n\n";

    struct tcp_info info;
    socklen_t len = sizeof(info);
    getsockopt(fd, IPPROTO_TCP, TCP_INFO, &info, &len);
    std::cout << "TCP state: " << (int)info.tcpi_state << "\n";

    close(fd);
    return 0;
}
