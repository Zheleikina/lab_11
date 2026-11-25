// Мінімальний власний тестовий каркас (без зовнішніх залежностей).
#include <climits>
#include <cmath>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

#include "lab11/part1.h"
#include "lab11/part2.h"
#include "lab11/part3.h"
#include "lab11/part4.h"
#include "lab11/part5.h"
#include "lab11/sales.h"

namespace {
int g_checks = 0;
int g_failed = 0;

void check(bool ok, const char* expr, int line) {
    ++g_checks;
    if (!ok) {
        ++g_failed;
        std::cerr << "ПРОВАЛ (рядок " << line << "): " << expr << '\n';
    }
}
#define CHECK(expr) check((expr), #expr, __LINE__)

bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }
}  // namespace

using Idx = std::vector<std::size_t>;

void test_part1() {
    using lab11::part1::indices_greater_than;
    CHECK((indices_greater_than({3, 8, 1, 6, 9, 5, 12, 2, 7}, 5) == Idx{1, 3, 4, 6, 8}));
    CHECK((indices_greater_than({5, 5, 5}, 5).empty()));  // строго більше
    CHECK((indices_greater_than({}, 5).empty()));
    CHECK((indices_greater_than({-10, 6}, 5) == Idx{1}));
    const std::vector<int> v{9, 1, 9};
    const auto copy = v;
    (void)indices_greater_than(v, 5);
    CHECK(v == copy);
}

void test_part2() {
    using lab11::part2::AbsValue;
    AbsValue abs;
    CHECK(abs(-5) == 5);
    CHECK(abs(5) == 5);
    CHECK(abs(0) == 0);
    CHECK(abs(INT_MIN) == 2147483648LL);  // без UB
    CHECK(abs(INT_MAX) == 2147483647LL);
    auto lambda = [](int x) -> long long { return x < 0 ? -static_cast<long long>(x) : x; };
    for (int x : {-7, 0, 13, INT_MIN, INT_MAX}) CHECK(abs(x) == lambda(x));
}

void test_part3() {
    using lab11::part3::increase_all;
    const std::vector<int> v{1, 2, -3};
    const auto r = increase_all(v, 10);
    CHECK((r == std::vector<int>{11, 12, 7}));
    CHECK((v == std::vector<int>{1, 2, -3}));  // вхід не змінився
    CHECK(increase_all({}, 5).empty());
    CHECK((increase_all(v, 0) == v));
    CHECK((increase_all(v, -1) == std::vector<int>{0, 1, -4}));
}

void test_part4() {
    using namespace lab11::part4;
    const std::vector<int> sample{5, -4, 12, 7, 2, -8, 9, 10, 3};
    CHECK(min_even_cube_classic(sample) == std::optional<long long>{-512});
    CHECK(min_even_cube_ranges(sample) == std::optional<long long>{-512});
    CHECK(!min_even_cube_classic({1, 3, 5}).has_value());
    CHECK(!min_even_cube_ranges(std::vector<int>{1, 3, 5}).has_value());
    CHECK(!min_even_cube_classic({}).has_value());
    CHECK(!min_even_cube_ranges(std::vector<int>{}).has_value());
    CHECK(min_even_cube_ranges(sample) == min_even_cube_classic(sample));
    // куб, що не вміщується в int (1500^3 = 3.375e9)
    CHECK(min_even_cube_classic({1500}) == std::optional<long long>{3375000000LL});
    CHECK(min_even_cube_ranges(std::vector<int>{1500}) == std::optional<long long>{3375000000LL});
    // ranges-версія працює і з view
    CHECK(min_even_cube_ranges(std::views::iota(1, 10)) == std::optional<long long>{8});
    // збіг на кількох наборах
    for (const auto& d : {std::vector<int>{2}, {-2, -4}, {0, 1}, {7, 7, 6, 6}}) {
        CHECK(min_even_cube_classic(d) == min_even_cube_ranges(d));
    }
}

void test_part5_average() {
    using lab11::part5::average;
    auto r = std::views::iota(1, 31) | std::views::filter([](int x) { return x % 3 == 0; }) |
             std::views::transform([](int x) { return x * x; });
    const auto a = average(r);
    CHECK(a.has_value() && near(*a, 346.5));
    auto none = std::views::iota(1, 5) | std::views::filter([](int x) { return x > 100; });
    CHECK(!average(none).has_value());
    const std::vector<int> v{2, 4, 9};
    CHECK(near(*average(v), 5.0));
    CHECK(near(*average(std::vector<int>{10, 20}), 15.0));
    CHECK(!average(std::vector<int>{}).has_value());
    CHECK(near(*average(std::vector<double>{0.5, 1.5}), 1.0));
}

void test_sales() {
    using namespace lab11::sales;
    const std::vector<Sale> s{{"A", 100.0, 2}, {"B", 50.0, 10}, {"C", 10.0, 5}, {"D", 60.0, 1}};
    CHECK(near(total_income(s), 260.0));  // A=200, D=60; B (рівно 50) не береться
    CHECK(s.size() == 4 && s[1].price == 50.0 && s[0].quantity == 2);  // вхід не змінено
    CHECK(near(total_income(std::vector<Sale>{}), 0.0));
    CHECK(near(total_income(std::vector<Sale>{{"X", 49.99, 3}}), 0.0));
    CHECK(near(total_income(std::vector<Sale>{{"X", 50.01, 2}}), 100.02));
    CHECK(near(sum_of(std::vector<double>{1.5, 2.5}), 4.0));
    CHECK(near(sum_of(std::vector<double>{}), 0.0));
    std::size_t n = 0;
    for (const Sale& x : expensive_sales(s)) { (void)x; ++n; }
    CHECK(n == 2);
}

int main() {
    test_part1();
    test_part2();
    test_part3();
    test_part4();
    test_part5_average();
    test_sales();
    std::cout << "Перевірок: " << g_checks << ", провалено: " << g_failed << '\n';
    return g_failed == 0 ? 0 : 1;
}
