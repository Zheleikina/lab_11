// Лабораторна робота №11, частина 5, завдання 1.
// std::remove_if: чому розмір вектора не змінюється, і як це виправити.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {

void print_vector(const std::string& title, const std::vector<int>& v) {
    std::cout << title << ": розмір " << v.size() << ':';
    std::for_each(v.begin(), v.end(), [](int x) { std::cout << ' ' << x; });
    std::cout << '\n';
}

}  // namespace

int main() {
    const std::vector<int> original{1, -2, 3, -4, 5};
    auto is_negative = [](int x) { return x < 0; };

    print_vector("Початковий вектор", original);

    // Як в оригіналі: remove_if без erase. Розмір не змінився.
    std::vector<int> only_remove = original;
    (void)std::remove_if(only_remove.begin(), only_remove.end(), is_negative);
    print_vector("Лише remove_if (помилка)", only_remove);

    // Виправлення 1: ідіома erase-remove.
    std::vector<int> erase_remove = original;
    erase_remove.erase(
        std::remove_if(erase_remove.begin(), erase_remove.end(), is_negative),
        erase_remove.end());
    print_vector("erase + remove_if", erase_remove);

    // Виправлення 2: std::erase_if (C++20), одна дія замість двох.
    std::vector<int> with_erase_if = original;
    const auto removed = std::erase_if(with_erase_if, is_negative);
    print_vector("std::erase_if", with_erase_if);
    std::cout << "Видалено елементів: " << removed << '\n';

    std::cout << "Обидва виправлення дали однаковий результат: "
              << (erase_remove == with_erase_if ? "так" : "ні") << '\n';
}
