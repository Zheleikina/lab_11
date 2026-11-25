// Частина 5, завдання 3 - ОРИГІНАЛЬНИЙ код з методички (без змін).
// Цей файл НЕ компілюється - так і задумано (див. пояснення в task3_fixed).
#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

std::vector<int> make() {
    return {3, 1, 4};
}

int main() {
    auto it = std::ranges::max_element(make());

    std::cout << *it << std::endl;
}
