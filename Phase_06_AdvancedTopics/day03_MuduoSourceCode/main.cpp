#include <iostream>

int main() {
    std::cout << "Muduo Network Library Source Code Analysis\n\n";
    std::cout << "Key concepts:\n";
    std::cout << "  - One loop per thread (event loop architecture)\n";
    std::cout << "  - Non-blocking I/O with epoll\n";
    std::cout << "  - Timer management via timerfd\n";
    std::cout << "  - Buffer design (zero-copy scatter/gather I/O)\n\n";

    std::cout << "Core components:\n";
    std::cout << "  EventLoop     - main event loop (poller wrapper)\n";
    std::cout << "  Channel       - fd + events + callbacks\n";
    std::cout << "  Poller        - epoll/poll abstraction\n";
    std::cout << "  TcpConnection - per-connection state machine\n";
    std::cout << "  Buffer        - application-level read/write buffer\n";
    std::cout << "  Timestamp     - high-resolution time point\n\n";

    std::cout << "Relevance to edge AI:\n";
    std::cout << "  - Muduo's Reactor pattern is the foundation\n";
    std::cout << "    for edge device service frameworks\n";
    std::cout << "  - Timer management is critical for periodic\n";
    std::cout << "    inference and health check\n";
    return 0;
}
