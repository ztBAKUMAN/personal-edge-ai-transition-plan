#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "Debug toolchain demo\n\n";
    std::cout << "Compile with: g++ -g -O0 main.cpp\n\n";
    std::cout << "Tools:\n";
    std::cout << "  gdb ./binary          - interactive debugger\n";
    std::cout << "  strace -f ./binary    - trace system calls\n";
    std::cout << "  ltrace ./binary       - trace library calls\n";
    std::cout << "  perf stat ./binary    - performance counters\n";
    std::cout << "  valgrind --leak-check=yes ./binary\n";
    std::cout << "  objdump -d ./binary   - disassembly\n";

    // Deliberate crash for gdb practice
    int* p = nullptr;
    (void)p;
    // Uncomment to practice: *p = 42;
    std::cout << "\n(gdb) break main\n(gdb) run\n(gdb) bt\n(gdb) info locals\n";
    return 0;
}
