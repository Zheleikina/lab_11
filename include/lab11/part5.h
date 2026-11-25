#pragma once
// Частина 5, завдання 4: виправлена функція average.
// Оригінальна версія (const R&) лежить у src/part5_task4_original.cpp.

#include <concepts>
#include <cstddef>
#include <numeric>
#include <optional>
#include <ranges>
#include <utility>

namespace lab11::part5 {

// Чому оригінал не компілювався: у нього параметр const R&. Для
// views::filter (і views::transform поверх нього) функції begin()/end()
// НЕ є const: filter_view при першому begin() шукає перший підходящий
// елемент і запам'ятовує його в собі, тобто мусить змінювати власний стан.
// Тому обійти такий view через const-посилання не можна.
//
// Виправлення:
//  * R&& (forwarding reference): приймає і lvalue, і rvalue, і не вимагає const;
//  * концепт input_range + перевірка, що елементи перетворюються на double;
//  * std::optional<double>: для порожнього діапазону середнього не існує.
//
// Сума й кількість рахуються за ОДИН прохід через std::accumulate зі станом
// std::pair. Так само працює для діапазонів, які можна пройти лише раз.
// views::common потрібен, бо std::accumulate приймає пару ітераторів одного
// типу, а деякі views мають інший тип кінця (sentinel).
template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>, double>
std::optional<double> average(R&& r) {
    auto common = std::views::all(std::forward<R>(r)) | std::views::common;

    const auto [sum, count] = std::accumulate(
        common.begin(), common.end(), std::pair<double, std::size_t>{0.0, 0},
        [](std::pair<double, std::size_t> acc, double x) {
            return std::pair<double, std::size_t>{acc.first + x, acc.second + 1};
        });

    if (count == 0) {
        return std::nullopt;
    }
    return sum / static_cast<double>(count);  // ділення в double
}

}  // namespace lab11::part5
