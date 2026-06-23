#include <iostream>

int main() {
    std::cout << "CI/CD for Edge AI Projects\n\n";
    std::cout << "Pipeline stages:\n";
    std::cout << "  1. Lint         — clang-tidy, cppcheck\n";
    std::cout << "  2. Build        — cmake, make -j$(nproc)\n";
    std::cout << "  3. Unit Test    — ctest, gtest/catch2\n";
    std::cout << "  4. Sanitizer    — ASan, UBSan, TSan\n";
    std::cout << "  5. Benchmark    — compare perf regressions\n";
    std::cout << "  6. Package      — deb/rpm/docker image\n";
    std::cout << "  7. Deploy       — SCP/OTA/K8s roll-out\n\n";

    std::cout << "GitHub Actions \".github/workflows/ci.yml\":\n";
    std::cout << "  name: CI\n";
    std::cout << "  on: [push, pull_request]\n";
    std::cout << "  jobs:\n";
    std::cout << "    build:\n";
    std::cout << "      runs-on: ubuntu-latest\n";
    std::cout << "      steps:\n";
    std::cout << "        - uses: actions/checkout@v4\n";
    std::cout << "        - run: cmake -B build && cmake --build build\n";
    return 0;
}
