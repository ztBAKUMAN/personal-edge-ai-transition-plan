#include <iostream>
#include <dlfcn.h>

int main() {
    std::cout << "Dynamic library loading demo\n";
    std::cout << "ldd, LD_LIBRARY_PATH, dlopen basics\n";

    void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle) {
        std::cout << "libc loaded successfully\n";
        dlclose(handle);
    } else {
        std::cerr << "dlopen error: " << dlerror() << "\n";
    }

    std::cout << "\nUse these tools to debug library issues:\n";
    std::cout << "  ldd ./binary        - list dynamic dependencies\n";
    std::cout << "  LD_DEBUG=libs ./bin - trace library loading\n";
    std::cout << "  readelf -d ./binary  - examine dynamic section\n";
    return 0;
}
