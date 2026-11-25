// Лабораторна робота №11, частина 5, завдання 3.
// Тимчасовий об'єкт і std::ranges::dangling.
//
// РЕЗУЛЬТАТ ОРИГІНАЛЬНОЇ ПРОГРАМИ: НЕ компілюється.
//   g++ 13:   error: no match for 'operator*' (operand type is
//             'std::ranges::dangling')
//   clang 18: error: indirection requires pointer operand
//             ('borrowed_iterator_t<vector<int>>' (aka 'std::ranges::dangling')
//             invalid)
//
// ПОЯСНЕННЯ. make() повертає тимчасовий вектор, який знищується в кінці
// рядка з max_element. Ітератор на його елемент після цього вказував би в
// звільнену пам'ять (висячий ітератор, UB). Щоб цього не сталося, алгоритми
// ranges для rvalue-контейнера (не "позичуваного" діапазону) повертають не
// ітератор, а спеціальний тип std::ranges::dangling. Його не можна
// розіменувати, тож помилка ловиться на етапі компіляції, а не в роботі
// програми.
//
// ВИПРАВЛЕННЯ: дати вектору ім'я, щоб він жив, поки ми користуємось ітератором.
//
// РЕЗУЛЬТАТ ВИПРАВЛЕНОЇ ПРОГРАМИ: Максимум: 4

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> make() {
    return {3, 1, 4};
}

int main() {
    // Спосіб 1: зберегти тимчасовий вектор у змінну, потім шукати.
    const auto data = make();
    const auto it = std::ranges::max_element(data);
    if (it != data.end()) {  // порожній вектор: it == end(), розіменовувати не можна
        std::cout << "Максимум: " << *it << std::endl;
    }

    // Спосіб 2: ranges::max повертає ЗНАЧЕННЯ, а не ітератор, тому з
    // тимчасовим об'єктом безпечний. Умова: діапазон не порожній (для
    // порожнього це UB), тому тут його довжина перевірена окремо.
    if (!data.empty()) {
        std::cout << "Максимум (ranges::max): " << std::ranges::max(make()) << std::endl;
    }
}
