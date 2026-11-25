// Лабораторна робота №11, частина 3 (варіант 3).
// Чиста функція increase_all та незмінність вхідних даних.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "lab11/part3.h"

namespace {

void print_line(const std::string& title, const std::vector<int>& values) {
    std::cout << title;
    if (values.empty()) {
        std::cout << " (порожній)";
    }
    std::for_each(values.begin(), values.end(), [](int x) { std::cout << ' ' << x; });
    std::cout << '\n';
}

void run_case(const std::string& name, const std::vector<int>& source, int value) {
    std::cout << "--- " << name << " (+" << value << ") ---\n";
    print_line("До виклику:    ", source);

    // Робимо копію "до", щоб автоматично перевірити, що source не змінився.
    const std::vector<int> snapshot = source;

    const std::vector<int> result = lab11::part3::increase_all(source, value);

    print_line("Після виклику: ", source);
    print_line("Результат:     ", result);
    std::cout << "Початковий вектор не змінився: "
              << (source == snapshot ? "так" : "НІ (помилка!)") << '\n';
}

}  // namespace

int main() {
    run_case("Звичайний вектор", {1, 2, 3, -4, 10}, 5);
    run_case("Від'ємна константа", {10, 20, 30}, -15);
    run_case("Порожній вектор", {}, 7);
}
