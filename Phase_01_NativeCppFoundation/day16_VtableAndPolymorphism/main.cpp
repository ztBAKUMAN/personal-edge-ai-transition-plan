#include <iostream>

class Animal {
public:
    virtual ~Animal() = default;
    virtual void speak() const = 0;
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof\n"; }
};

class Cat : public Animal {
public:
    void speak() const override { std::cout << "Meow\n"; }
};

struct VTableDemo {
    int data;
    virtual void func1() { std::cout << "func1\n"; }
    virtual void func2() { std::cout << "func2\n"; }
};

int main() {
    Dog dog; Cat cat;
    Animal* animals[] = {&dog, &cat};
    for (auto* a : animals) a->speak();

    std::cout << "sizeof VTableDemo: " << sizeof(VTableDemo)
              << " (includes vptr)\n";
    return 0;
}
