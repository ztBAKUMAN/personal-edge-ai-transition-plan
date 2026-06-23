#include <iostream>

// Demo: shared library interface vs static library ABI
// In practice: define interface in header, compile as .so or .a
int main() {
    std::cout << "Shared lib / Static lib / ABI boundary demo\n";
    std::cout << "This project is structured to support both:\n";
    std::cout << "  - add_library(edge_core STATIC ...)\n";
    std::cout << "  - add_library(edge_core SHARED ...)\n";
    return 0;
}
