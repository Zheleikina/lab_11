#pragma once
// Частина 6 (додаткове завдання, варіант 3): аналіз продажів.
// Умова:
//   * відібрати товари, ціна яких перевищує 50;
//   * дохід від позиції = ціна * кількість;
//   * загальний дохід = сума доходів відібраних позицій.
// Відбір і перетворення - std::views::filter / std::views::transform,
// агрегування - чиста функція total_income.

#include <concepts>
#include <numeric>
#include <ranges>
#include <string>
#include <utility>

namespace lab11::sales {

struct Sale {
    std::string product;
    double price;
    int quantity;
};

inline constexpr double kPriceThreshold = 50.0;

inline bool is_expensive(const Sale& s) noexcept { return s.price > kPriceThreshold; }
inline double income(const Sale& s) noexcept { return s.price * s.quantity; }

template <class R>
concept SaleRange = std::ranges::input_range<R> &&
                    std::same_as<std::remove_cvref_t<std::ranges::range_reference_t<R>>, Sale>;

template <SaleRange R>
auto expensive_sales(R&& sales) {
    return std::forward<R>(sales) | std::views::filter(is_expensive);
}

// Етап 2: дохід від кожної такої позиції (теж лінивий).
template <SaleRange R>
auto expensive_incomes(R&& sales) {
    return expensive_sales(std::forward<R>(sales)) | std::views::transform(income);
}


template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>, double>
double sum_of(R&& values) {
    auto common = std::views::all(std::forward<R>(values)) | std::views::common;
    return std::accumulate(common.begin(), common.end(), 0.0);
}

template <SaleRange R>
double total_income(R&& sales) {
    return sum_of(expensive_incomes(std::forward<R>(sales)));
}

}  // namespace lab11::sales
