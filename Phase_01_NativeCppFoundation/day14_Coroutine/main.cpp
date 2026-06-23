#include <iostream>
#if __has_include(<coroutine>)
#include <coroutine>

struct Generator {
    struct promise_type {
        int current_value;
        auto get_return_object() { return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
        auto yield_value(int value) {
            current_value = value;
            return std::suspend_always{};
        }
    };
    std::coroutine_handle<promise_type> handle;
    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }
    bool next() { handle.resume(); return !handle.done(); }
    int value() { return handle.promise().current_value; }
};

Generator counter() {
    for (int i = 0; i < 5; ++i) co_yield i;
}

int main() {
    auto gen = counter();
    while (gen.next()) {
        std::cout << "Yielded: " << gen.value() << "\n";
    }
    return 0;
}
#else
int main() {
    std::cout << "Coroutines require C++20 (GCC 10+/Clang 14+)\n";
    return 0;
}
#endif
