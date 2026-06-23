#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

constexpr const char* SHM_NAME = "/edge_ai_shm";
constexpr size_t SHM_SIZE = 4096;

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHM_SIZE);
    void* ptr = mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    const char* msg = "Hello from shared memory!";
    memcpy(ptr, msg, strlen(msg) + 1);
    std::cout << "Written to SHM: " << static_cast<char*>(ptr) << "\n";

    munmap(ptr, SHM_SIZE);
    shm_unlink(SHM_NAME);
    return 0;
}
