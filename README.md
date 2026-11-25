# Лабораторна робота №11. Основи функціонального програмування в C++

Варіант 3. Стандарт C++23, збірка через CMake, зовнішніх бібліотек немає.

## Що де лежить

| Частина | Завдання варіанта 3 | Файли |
|---|---|---|
| 1. Лямбди й алгоритми | №3: індекси елементів > 5 | `include/lab11/part1.h`, `src/part1_lambdas.cpp` |
| 2. Функтори | №3: `AbsValue` + еквівалентна лямбда | `include/lab11/part2.h`, `src/part2_functors.cpp` |
| 3. Чисті функції | №3: збільшити всі елементи на константу | `include/lab11/part3.h`, `src/part3_pure_functions.cpp` |
| 4. Конвеєри | №3: парні → куби → мінімум (STL і ranges) | `include/lab11/part4.h`, `src/part4_pipelines.cpp` |
| 5. Аналіз помилок | усі 4 завдання | `src/part5_taskN_original.cpp`, `src/part5_taskN_fixed.cpp`, `include/lab11/part5.h` |
| 6. Додаткове | №3: аналіз продажів | `include/lab11/sales.h`, `src/part6_sales.cpp` |
| Тести | | `tests/tests.cpp` + перевірки виводу в `CMakeLists.txt` |

Для частини 5 оригінальний код із методички лежить у `*_original.cpp`
(без змін), виправлений і пояснений - у `*_fixed.cpp`. Оригінали завдань 3 і 4
не компілюються, і це очікувано: тест `p5_taskN_original_does_not_compile`
проходить саме тоді, коли збірка падає.

## Збірка і запуск

Потрібні компілятор з C++23 і ranges (GCC 13+, Clang 17+/libstdc++ 13, MSVC 19.37+) та CMake 3.20+.

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/part4_pipelines          # будь-яка з програм
```

Усе одразу (збірка, тести, збереження виводів у `out/`): `./scripts/run_all.sh`.

Подивитись помилку компілятора в оригіналах:

```bash
cmake --build build --target part5_task3_original
cmake --build build --target part5_task4_original
```

На Windows (MSVC) консоль може потребувати UTF-8 для української мови: `chcp 65001`.

## Дотримані вимоги методички

- C++23; вхідні колекції не змінюються (`const&`, нові контейнери на виході);
- обчислення без побічних ефектів, друк - окремо, у `main`;
- лямбди для локальної логіки, іменовані функції для повторної (`is_even`, `cube`, `income`);
- агрегування через `std::accumulate`;
- можливо відсутній результат - `std::optional`; ділення - у `double`;
- функції, що приймають діапазони, беруть `R&&` (або значення), а не `const R&`;
- порожні вхідні дані оброблено (і перевірено тестами).
