#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

int main() {
    fs::path dir = "test_dir";
    fs::create_directories(dir);
    std::ofstream(dir / "data.bin").put('A');
    std::cout << "File created: " << fs::file_size(dir / "data.bin") << " bytes\n";
    std::cout << "Platform: "
#ifdef _WIN32
              << "Windows"
#elif __linux__
              << "Linux"
#else
              << "Other"
#endif
              << "\n";
    fs::remove_all(dir);
    return 0;
}
