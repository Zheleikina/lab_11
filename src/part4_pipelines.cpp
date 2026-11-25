// Лабораторна робота №11, частина 4 (варіант 3).
// Парні -> куби -> мінімум. Класичний конвеєр і конвеєр на std::ranges.

#include <algorithm>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

#include "lab11/part4.h"

namespace {

template <class T>
void print_line(const std::string& title, const std::vector<T>& values) {
    std::cout << title;
    if (values.empty()) {
        std::cout << " (порожній)";
    }
    std::for_each(values.begin(), values.end(),
                  [](const T& x) { std::cout << ' ' << x; });
    std::cout << '\n';
}

void print_optional(const std::string& title, const std::optional<long long>& value) {
    std::cout << title;
    if (value) {
        std::cout << *value;
    } else {
        std::cout << "відсутнє (nullopt)";
    }
    std::cout << '\n';
}

void run_case(const std::string& name, const std::vector<int>& data) {
    std::cout << "--- " << name << " ---\n";
    print_line("Вхідні дані:", data);

    // Обидві реалізації отримують ОДНАКОВІ дані.
    const auto classic = lab11::part4::min_even_cube_classic(data);
    const auto with_ranges = lab11::part4::min_even_cube_ranges(data);

    print_optional("А. Класичний варіант: ", classic);
    print_optional("Б. Варіант ranges:    ", with_ranges);
    std::cout << "Результати збігаються: " << (classic == with_ranges ? "так" : "НІ") << '\n';
}

// Демонстрація ліні. Лічильники в лямбдах - це побічний ефект, тому такий
// код тільки для показу й у "чисті" функції проєкту не потрапляє.
void show_laziness(const std::vector<int>& data) {
    std::cout << "--- Коли саме ranges виконує роботу ---\n";
    int filter_calls = 0;
    int transform_calls = 0;

    auto pipeline =
        data | std::views::filter([&filter_calls](int x) {
                   ++filter_calls;
                   return lab11::part4::is_even(x);
               })
             | std::views::transform([&transform_calls](int x) {
                   ++transform_calls;
                   return lab11::part4::cube(x);
               });

    std::cout << "Конвеєр створено:        виклики фільтра = " << filter_calls
              << ", виклики transform = " << transform_calls << '\n';

    const auto it = std::ranges::min_element(pipeline);

    std::cout << "Після min_element:       виклики фільтра = " << filter_calls
              << ", виклики transform = " << transform_calls << '\n';
    std::cout << "Мінімум = " << *it << '\n';
    const auto evens = std::count_if(data.begin(), data.end(), lab11::part4::is_even);
    std::cout << "Елементів у даних: " << data.size() << ", з них парних: " << evens << '\n'
              << "Фільтр викликається по разу на кожен елемент даних. Transform викликається\n"
              << "частіше, ніж є парних: представлення перераховує значення при кожному\n"
              << "розіменуванні ітератора, а min_element розіменовує елементи під час\n"
              << "порівнянь (точне число залежить від реалізації стандартної бібліотеки).\n";
}

}  // namespace

int main() {
    const std::vector<int> sample{5, -4, 12, 7, 2, -8, 9, 10, 3};

    run_case("Звичайні дані", sample);
    run_case("Усі числа непарні", {1, 3, 5, 7});
    run_case("Порожній вектор", {});
    run_case("Один парний елемент", {7, 8, 9});

    show_laziness(sample);
}
