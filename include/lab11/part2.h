#pragma once
// Частина 2, варіант 3: функтор AbsValue.
// Умова: повертає абсолютне значення переданого числа.

namespace lab11::part2 {

// Функтор без стану: клас з перевантаженим operator().
//
// Результат має тип long long, а не int. Причина: abs(INT_MIN) = 2147483648
// не вміщується в int, і std::abs(INT_MIN) дає невизначену поведінку.
// Якщо спершу розширити тип до long long, то мінус змінює знак безпечно.
struct AbsValue {
    long long operator()(int x) const noexcept {
        const long long wide = x;
        return wide < 0 ? -wide : wide;
    }
};

}  // namespace lab11::part2
