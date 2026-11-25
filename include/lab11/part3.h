#pragma once
// Частина 3, варіант 3.
// Умова: збільшити всі елементи вектора на задану константу та повернути
// результат, не змінюючи початковий вектор.

#include <algorithm>
#include <iterator>
#include <vector>

namespace lab11::part3 {

// Чиста функція:
//  * вхід - const& (змінити його через цей параметр неможливо);
//  * результат - новий вектор;
//  * нічого не читає й не пише поза своїми параметрами, нічого не друкує.
// Для однакових (source, value) завжди повертає однаковий результат.
//
// Увага: переповнення int не перевіряється (це поза умовою завдання),
// тому тестові значення підібрано так, щоб сума вміщувалась в int.
inline std::vector<int> increase_all(const std::vector<int>& source, int value) {
    std::vector<int> result;
    result.reserve(source.size());
    std::transform(source.begin(), source.end(), std::back_inserter(result),
                   [value](int x) { return x + value; });
    return result;
}

}  // namespace lab11::part3
