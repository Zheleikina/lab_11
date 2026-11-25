// Лабораторна робота №11, частина 5, завдання 4.
// Передавання діапазону у функцію: const R& проти R&&.
//
// РЕЗУЛЬТАТ ОРИГІНАЛЬНОЇ ПРОГРАМИ: НЕ компілюється.
//   g++ 13:   error: passing 'const std::ranges::transform_view<...>' as
//             'this' argument discards qualifiers (виклик begin() у range-for)
//   clang 18: error: no matching member function for call to 'begin'
//
// ПОЯСНЕННЯ. Параметр const R& робить представлення константним, а
// begin() у filter_view (і в transform_view над ним) не є const: filter_view
// при першому begin() шукає перший підходящий елемент і кешує його, тобто
// змінює себе. Через const це неможливо.
//
// ВИПРАВЛЕННЯ (див. include/lab11/part5.h): параметр R&& (forwarding
// reference) + концепт input_range, результат std::optional<double> для
// порожнього діапазону, один прохід через std::accumulate.
//
// РЕЗУЛЬТАТ ВИПРАВЛЕНОЇ ПРОГРАМИ:
//   Середнє: 346.5   (числа 3,6,...,30 -> квадрати -> сума 3465 / 10)

#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

#include "lab11/part5.h"

int main() {
    using lab11::part5::average;

    auto r = std::views::iota(1, 31)
           | std::views::filter([](int x) { return x % 3 == 0; })
           | std::views::transform([](int x) { return x * x; });

    // Результат тепер optional: перевіряємо, чи він є.
    if (const auto avg = average(r)) {
        std::cout << "Середнє: " << *avg << std::endl;
    } else {
        std::cout << "Діапазон порожній, середнього немає" << std::endl;
    }

    // Порожній діапазон: фільтр нічого не пропускає.
    auto nothing = std::views::iota(1, 31)
                 | std::views::filter([](int x) { return x > 100; });
    const auto empty_avg = average(nothing);
    std::cout << "Порожній діапазон: "
              << (empty_avg ? "є середнє" : "середнього немає (nullopt)") << std::endl;

    // Працює і зі звичайним контейнером, і з тимчасовим (rvalue) об'єктом.
    const std::vector<int> v{2, 4, 9};
    std::cout << "Вектор {2, 4, 9}: " << *average(v) << std::endl;
    std::cout << "Тимчасовий вектор {10, 20}: " << *average(std::vector<int>{10, 20})
              << std::endl;
}
