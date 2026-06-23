#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cstring>

int main() {
    const char* filepath = "/tmp/mmap_demo.bin";
    int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    size_t size = 4096;
    ftruncate(fd, size);

    // Memory-mapped file I/O (zero-copy)
    void* mapped = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    const char* msg = "Zero-copy via mmap!";
    memcpy(mapped, msg, strlen(msg) + 1);
    std::cout << "Written: " << static_cast<char*>(mapped) << "\n";

    munmap(mapped, size);
    unlink(filepath);
    return 0;
}
