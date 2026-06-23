#include <iostream>

int main() {
    std::cout << "Cross-Compilation for Edge AI\n\n";
    std::cout << "Common targets:\n";
    std::cout << "  aarch64-linux-gnu (ARM64, e.g. RK3588)\n";
    std::cout << "  arm-linux-gnueabihf (ARM32)\n\n";

    std::cout << "Toolchain setup:\n";
    std::cout << "  sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu\n\n";

    std::cout << "CMake cross-compile:\n";
    std::cout << "  cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-aarch64.cmake ..\n\n";

    std::cout << "toolchain-aarch64.cmake:\n";
    std::cout << "  set(CMAKE_SYSTEM_NAME Linux)\n";
    std::cout << "  set(CMAKE_SYSTEM_PROCESSOR aarch64)\n";
    std::cout << "  set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)\n\n";

    std::cout << "Dependency cross-build:\n";
    std::cout << "  ./configure --host=aarch64-linux-gnu --prefix=$SYSROOT\n";
    std::cout << "  make && make install\n";
    return 0;
}
