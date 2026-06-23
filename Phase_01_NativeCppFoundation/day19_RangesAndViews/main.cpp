#include <iostream>
#include <ranges>
#include <vector>
#include <span>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
    auto even = data | std::views::filter([](int n) { return n % 2 == 0; })
                     | std::views::transform([](int n) { return n * n; });
    std::cout << "Even squares: ";
    for (int n : even) std::cout << n << " ";
    std::cout << "\n";

    std::span<int> span(data);
    std::cout << "Span size=" << span.size() << " first=" << span[0] << "\n";
    return 0;
}
