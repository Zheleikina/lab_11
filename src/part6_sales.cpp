// Лабораторна робота №11, частина 6 (додаткове завдання, варіант 3).
// Аналіз продажів: filter -> transform -> accumulate.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "lab11/sales.h"

namespace {

using lab11::sales::Sale;

void print_sales(const std::vector<Sale>& sales) {
    std::for_each(sales.begin(), sales.end(), [](const Sale& s) {
        std::cout << "  " << std::left << std::setw(10) << s.product << std::right
                  << std::setw(8) << s.price << " x " << s.quantity << '\n';
    });
}

void run_case(const std::string& name, const std::vector<Sale>& sales) {
    std::cout << "--- " << name << " ---\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Усі позиції:\n";
    print_sales(sales);

    // Копія для перевірки, що вхідні дані не змінилися.
    const std::vector<Sale> snapshot = sales;

    std::cout << "Позиції з ціною > " << lab11::sales::kPriceThreshold << ":\n";
    std::ranges::for_each(lab11::sales::expensive_sales(sales), [](const Sale& s) {
        std::cout << "  " << std::left << std::setw(10) << s.product << std::right
                  << " дохід = " << lab11::sales::income(s) << '\n';
    });

    std::cout << "Загальний дохід: " << lab11::sales::total_income(sales) << '\n';

    const bool unchanged =
        std::ranges::equal(sales, snapshot, [](const Sale& a, const Sale& b) {
            return a.product == b.product && a.price == b.price && a.quantity == b.quantity;
        });
    std::cout << "Початкові дані не змінилися: " << (unchanged ? "так" : "НІ") << '\n';
}

}  // namespace

int main() {
    const std::vector<Sale> sales{
        {"Laptop", 1200.0, 2}, {"Mouse", 25.5, 10}, {"Monitor", 300.0, 3},
        {"Cable", 50.0, 100},  // ціна рівно 50: умова "більше за 50" не виконується
        {"Keyboard", 75.5, 4}, {"Pen", 1.2, 500},
    };

    run_case("Звичайний набір", sales);
    run_case("Жодна ціна не перевищує 50", {{"Pen", 1.2, 500}, {"Cable", 50.0, 100}});
    run_case("Порожній набір", {});

    // Тимчасовий контейнер теж можна передати (rvalue -> R&&).
    std::cout << "--- Тимчасовий вектор ---\n";
    std::cout << "Загальний дохід: "
              << lab11::sales::total_income(std::vector<Sale>{{"TV", 500.0, 1}}) << '\n';
}
