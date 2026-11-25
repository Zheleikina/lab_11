// Частина 5, завдання 2 - ОРИГІНАЛЬНИЙ код з методички (без змін).
#include <iostream>

int main() {
    int k = 2;

    auto byValue = [k](int x) {
        return x * k;
    };

    auto byRef = [&k](int x) {
        return x * k;
    };

    k = 10;

    std::cout << byValue(3) << ' '
              << byRef(3) << std::endl;
}
