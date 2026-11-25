// Лабораторна робота №11, частина 2 (варіант 3).
// Функціональні об'єкти: AbsValue + еквівалентна лямбда.

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

#include "lab11/part2.h"

namespace {

template <class T>
void print_line(const std::string& title, const std::vector<T>& values) {
    std::cout << title;
    std::for_each(values.begin(), values.end(),
                  [](const T& x) { std::cout << ' ' << x; });
    std::cout << '\n';
}

}  // namespace

int main() {
    using lab11::part2::AbsValue;

    const std::vector<int> data{-5, 3, 0, -12, 7, INT_MIN, INT_MAX};
    print_line("Початковий вектор:   ", data);

    // 1) Функтор. std::transform обирають тому, що треба перетворити кожен
    //    елемент 1:1 у новий вектор. Передаємо об'єкт AbsValue{}; алгоритм
    //    викликає його як звичайну функцію.
    std::vector<long long> by_functor(data.size());
    std::transform(data.begin(), data.end(), by_functor.begin(), AbsValue{});
    print_line("Результат (функтор): ", by_functor);

    // 2) Еквівалентна лямбда: та сама логіка, але без окремого класу.
    //    Тип результату вказано явно (-> long long), щоб збігався з функтором.
    auto abs_lambda = [](int x) -> long long {
        const long long wide = x;
        return wide < 0 ? -wide : wide;
    };
    std::vector<long long> by_lambda(data.size());
    std::transform(data.begin(), data.end(), by_lambda.begin(), abs_lambda);
    print_line("Результат (лямбда):  ", by_lambda);

    std::cout << "Результати збігаються: " << (by_functor == by_lambda ? "так" : "ні")
              << '\n';

    // Перевірка: абсолютні значення не бувають від'ємними.
    const bool all_non_negative = std::all_of(by_functor.begin(), by_functor.end(),
                                              [](long long x) { return x >= 0; });
    std::cout << "Усі значення невід'ємні: " << (all_non_negative ? "так" : "ні") << '\n';

    // Порівняння за розміром: обидва об'єкти порожні (без стану), тому
    // займають по 1 байту.
    std::cout << "sizeof(AbsValue) = " << sizeof(AbsValue)
              << ", sizeof(лямбда) = " << sizeof(abs_lambda) << '\n';

    // AbsValue - функтор БЕЗ стану, тому накопичувати й повертати нічого.
    // Для функторів зі станом (наприклад, лічильник викликів) результат
    // беруть із об'єкта, який повертає std::for_each:
    //     auto counter = std::for_each(v.begin(), v.end(), CountCalls{});
    //     counter.count();
}
