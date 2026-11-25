#pragma once
// Частина 1, варіант 3.
// Умова: вивести індекси елементів вектора, значення яких більші за 5.
// Індексація починається з нуля.

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <vector>

namespace lab11::part1 {

// Чиста функція: нічого не друкує, вхідний вектор не змінює, результат
// повертає новим вектором.
//
// Чому саме ці алгоритми:
//  * std::iota      - генерує послідовність індексів 0, 1, 2, ... Власного
//                     циклу з лічильником не потрібно.
//  * std::copy_if   - потрібно залишити лише частину індексів і нічого не
//                     перетворювати, тобто це саме "відбір за умовою".
//                     (std::remove_if тут не підходить: він змінює контейнер,
//                     а початкові дані чіпати не можна.)
//  * лямбда         - умова "data[i] > threshold" потрібна лише в цьому
//                     місці, тому окрема іменована функція зайва. Вектор
//                     захоплюється за посиланням (без копіювання), поріг -
//                     за значенням.
inline std::vector<std::size_t> indices_greater_than(const std::vector<int>& data,
                                                     int threshold) {
    std::vector<std::size_t> all_indices(data.size());
    std::iota(all_indices.begin(), all_indices.end(), std::size_t{0});

    std::vector<std::size_t> result;
    std::copy_if(all_indices.begin(), all_indices.end(), std::back_inserter(result),
                 [&data, threshold](std::size_t i) { return data[i] > threshold; });
    return result;
}

}  // namespace lab11::part1
