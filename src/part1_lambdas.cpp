// Лабораторна робота №11, частина 1 (варіант 3).
// Лямбда-вирази та стандартні алгоритми: індекси елементів, більших за 5.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "lab11/part1.h"

namespace {

// Виведення живе окремо від обчислень. Для друку елементів, за умовою,
// використовуємо std::for_each: він просто застосовує лямбду до кожного
// елемента й нічого не повертає, а саме це нам і треба.
template <class T>
void print_line(const std::string& title, const std::vector<T>& values) {
    std::cout << title;
    std::for_each(values.begin(), values.end(),
                  [](const T& x) { std::cout << ' ' << x; });
    std::cout << '\n';
}

void run_case(const std::string& name, const std::vector<int>& data, int threshold) {
    std::cout << "--- " << name << " ---\n";
    print_line("Вектор:   ", data);

    const auto indices = lab11::part1::indices_greater_than(data, threshold);

    std::cout << "Індекси елементів > " << threshold << ':';
    if (indices.empty()) {
        std::cout << " (таких немає)\n";
    } else {
        std::for_each(indices.begin(), indices.end(),
                      [](std::size_t i) { std::cout << ' ' << i; });
        std::cout << '\n';
    }
}

}  // namespace

int main() {
    run_case("Звичайний вектор", {3, 8, 1, 6, 9, 5, 12, 2, 7}, 5);
    run_case("Елементи, рівні порогу, не беруться", {5, 5, 5, 6}, 5);
    run_case("Жодного елемента > 5", {1, 2, 3, 5}, 5);
    run_case("Порожній вектор", {}, 5);
}
