#!/usr/bin/env bash
# Збирає проєкт, запускає тести й усі програми, виводи кладе в out/.
set -euo pipefail
cd "$(dirname "$0")/.."

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure

mkdir -p out
for p in part1_lambdas part2_functors part3_pure_functions part4_pipelines part6_sales \
         part5_task1_original part5_task1_fixed part5_task2_original part5_task2_fixed \
         part5_task3_fixed part5_task4_fixed; do
  echo "== $p"
  ./build/$p | tee "out/$p.txt"
done

# Оригінали завдань 3 і 4 не компілюються 
for n in 3 4; do
  cmake --build build --target part5_task${n}_original > "out/part5_task${n}_original_compile_errors.txt" 2>&1 || true
done
echo "Готово. Результати в out/"
