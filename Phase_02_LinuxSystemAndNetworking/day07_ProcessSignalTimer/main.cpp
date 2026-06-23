#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <chrono>
#include <thread>

volatile sig_atomic_t signal_received = 0;
void handler(int sig) { signal_received = sig; }

int main() {
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    std::cout << "PID: " << getpid() << " - Try: kill -SIGINT " << getpid() << "\n";

    int timeout = 5;
    while (timeout-- > 0 && !signal_received) {
        std::cout << "Waiting... (" << timeout << "s left)\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (signal_received) {
        std::cout << "Signal " << signal_received << " received, exiting\n";
    }

    // Process creation demo
    pid_t pid = fork();
    if (pid == 0) {
        std::cout << "Child process: " << getpid() << "\n";
        _exit(0);
    } else {
        wait(nullptr);
        std::cout << "Child exited\n";
    }
    return 0;
}
