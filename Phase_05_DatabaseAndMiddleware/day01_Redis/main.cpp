#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class RedisClient {
public:
    RedisClient(const std::string& host, int port) {
        fd_ = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, host.c_str(), &addr.sin_addr);
        connect(fd_, (sockaddr*)&addr, sizeof(addr));
    }
    ~RedisClient() { close(fd_); }

    void set(const std::string& key, const std::string& value) {
        std::string cmd = "*3\r\n$3\r\nSET\r\n$" +
            std::to_string(key.size()) + "\r\n" + key + "\r\n$" +
            std::to_string(value.size()) + "\r\n" + value + "\r\n";
        send(fd_, cmd.data(), cmd.size(), 0);
    }

private:
    int fd_;
};

int main() {
    std::cout << "Redis Integration for Edge AI\n\n";
    std::cout << "Use cases:\n";
    std::cout << "  - Model config cache\n";
    std::cout << "  - Inference result stream\n";
    std::cout << "  - Device status reporting\n\n";

    std::cout << "API types:\n";
    std::cout << "  1. hiredis (C library)\n";
    std::cout << "  2. redis-plus-plus (C++ wrapper)\n";
    std::cout << "  3. Direct RESP protocol (as above)\n\n";

    std::cout << "Example:\n";
    std::cout << "  redis-cli SET model:yolo:path /models/yolov8s.onnx\n";
    std::cout << "  redis-cli GET model:yolo:path\n";
    return 0;
}
