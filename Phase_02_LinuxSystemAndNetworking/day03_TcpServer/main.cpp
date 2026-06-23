#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <thread>

void handleClient(int client_fd) {
    const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
    send(client_fd, response, strlen(response), 0);
    close(client_fd);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    std::cout << "TCP server listening on :8080\n";
    for (int i = 0; i < 3; ++i) {
        int client = accept(server_fd, nullptr, nullptr);
        if (client > 0) {
            std::thread(handleClient, client).detach();
        }
    }
    close(server_fd);
    return 0;
}
