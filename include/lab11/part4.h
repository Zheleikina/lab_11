#pragma once
// Частина 4, варіант 3.
// Умова: вибрати парні числа, обчислити їх куби й знайти мінімальне значення.
// Якщо після фільтрації нічого не залишилось - мінімум відсутній (nullopt).
//
// Два способи:
//   А. класичний - послідовність алгоритмів STL з проміжними контейнерами;
//   Б. std::ranges - фільтр і перетворення як ліниві представлення (views).

#include <algorithm>
#include <concepts>
#include <iterator>
#include <optional>
#include <ranges>
#include <vector>

namespace lab11::part4 {

// Іменовані функції, бо їх використовують обидві реалізації (повторне
// використання логіки, вимога 4 методички).
constexpr bool is_even(int x) noexcept { return x % 2 == 0; }  // працює й для від'ємних

// Куб рахуємо в long long: у int він переповниться вже для |x| > 1290.
// Точний результат гарантовано для |x| <= 2 097 151 (інакше не вміщується
// навіть у long long); тестові дані цієї межі не перевищують.
constexpr long long cube(int x) noexcept {
    const long long wide = x;
    return wide * wide * wide;
}

// ---------------------------------------------------------------------------
// А. Класична реалізація
// ---------------------------------------------------------------------------
// Етап 1. std::copy_if   - відібрати парні  -> проміжний контейнер evens.
// Етап 2. std::transform - піднести до куба -> проміжний контейнер cubes.
// Етап 3. std::min_element - знайти найменший куб.
// Кожен етап проходить усі свої дані повністю й кладе результат у новий
// вектор, тому тут ДВА проміжні контейнери.
inline std::optional<long long> min_even_cube_classic(const std::vector<int>& data) {
    std::vector<int> evens;
    std::copy_if(data.begin(), data.end(), std::back_inserter(evens), is_even);

    std::vector<long long> cubes(evens.size());
    std::transform(evens.begin(), evens.end(), cubes.begin(), cube);

    const auto it = std::min_element(cubes.begin(), cubes.end());
    if (it == cubes.end()) {  // порожній cubes: парних не було
        return std::nullopt;
    }
    return *it;
}

// ---------------------------------------------------------------------------
// Б. Реалізація з std::ranges
// ---------------------------------------------------------------------------
// Приймаємо діапазон як R&& (forwarding reference), а не const R&: деякі
// views не можна обходити через const (див. частину 5, завдання 4).
//
// views::filter і views::transform НІЧОГО не обчислюють у момент створення:
// вони лише запам'ятовують, що треба буде зробити. Реальна фільтрація та
// піднесення до куба відбуваються під час обходу, тобто всередині
// ranges::min_element. Проміжних контейнерів немає взагалі: елемент
// проходить фільтр -> куб -> порівняння по одному.
//
// Матеріалізація тут не потрібна: min_element не вимагає ні сортування,
// ні видалення повторів, йому достатньо проходу вперед (forward_range).
template <std::ranges::forward_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>, int>
std::optional<long long> min_even_cube_ranges(R&& data) {
    auto cubes = std::forward<R>(data)               // джерело
               | std::views::filter(is_even)         // лише парні (ліниво)
               | std::views::transform(cube);        // куб кожного (ліниво)

    const auto it = std::ranges::min_element(cubes);  // тут усе й виконується
    if (it == std::ranges::end(cubes)) {
        return std::nullopt;
    }
    return *it;
}

}  // namespace lab11::part4
