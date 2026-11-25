cmake_minimum_required(VERSION 3.20)
project(lab11_functional_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lab11_common INTERFACE)
target_include_directories(lab11_common INTERFACE ${CMAKE_SOURCE_DIR}/include)
if(MSVC)
  target_compile_options(lab11_common INTERFACE /W4 /utf-8 /EHsc)
else()
  target_compile_options(lab11_common INTERFACE -Wall -Wextra -Wpedantic)
endif()

# --- Основні програми (частини 1-4, 6) ---
foreach(name part1_lambdas part2_functors part3_pure_functions part4_pipelines part6_sales)
  add_executable(${name} src/${name}.cpp)
  target_link_libraries(${name} PRIVATE lab11_common)
endforeach()

# --- Частина 5: виправлені версії збираються завжди ---
foreach(n 1 2 3 4)
  add_executable(part5_task${n}_fixed src/part5_task${n}_fixed.cpp)
  target_link_libraries(part5_task${n}_fixed PRIVATE lab11_common)
endforeach()

# --- Частина 5: оригінали. 1 і 2 компілюються (збираються завжди);
# 3 і 4 - ні (так і задумано), тому з типової збірки їх виключено.
# Переконатися вручну:  cmake --build build --target part5_task3_original
foreach(n 1 2)
  add_executable(part5_task${n}_original src/part5_task${n}_original.cpp)
  target_link_libraries(part5_task${n}_original PRIVATE lab11_common)
endforeach()
foreach(n 3 4)
  add_executable(part5_task${n}_original EXCLUDE_FROM_ALL src/part5_task${n}_original.cpp)
  target_link_libraries(part5_task${n}_original PRIVATE lab11_common)
endforeach()

# --- Тести ---
enable_testing()

add_executable(lab11_tests tests/tests.cpp)
target_link_libraries(lab11_tests PRIVATE lab11_common)
add_test(NAME unit_tests COMMAND lab11_tests)

# Перевірка виводу програм частини 5 (оригінал і виправлення).
add_test(NAME p5_task1_original_keeps_negatives COMMAND part5_task1_original)
add_test(NAME p5_task1_fixed COMMAND part5_task1_fixed)
add_test(NAME p5_task2_original COMMAND part5_task2_original)
add_test(NAME p5_task2_fixed COMMAND part5_task2_fixed)
add_test(NAME p5_task3_fixed COMMAND part5_task3_fixed)
add_test(NAME p5_task4_fixed COMMAND part5_task4_fixed)
set_tests_properties(p5_task1_original_keeps_negatives PROPERTIES
  PASS_REGULAR_EXPRESSION "^5\n1 3 5")
set_tests_properties(p5_task1_fixed PROPERTIES
  PASS_REGULAR_EXPRESSION "erase \\+ remove_if: розмір 3: 1 3 5")
set_tests_properties(p5_task2_original PROPERTIES PASS_REGULAR_EXPRESSION "^6 30")
set_tests_properties(p5_task2_fixed PROPERTIES PASS_REGULAR_EXPRESSION "6 30")
set_tests_properties(p5_task3_fixed PROPERTIES PASS_REGULAR_EXPRESSION "Максимум: 4")
set_tests_properties(p5_task4_fixed PROPERTIES PASS_REGULAR_EXPRESSION "346.5")

# Оригінали завдань 3 і 4 МАЮТЬ не компілюватися: тест проходить, якщо збірка падає.
foreach(n 3 4)
  add_test(NAME p5_task${n}_original_does_not_compile
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target part5_task${n}_original)
  set_tests_properties(p5_task${n}_original_does_not_compile PROPERTIES WILL_FAIL TRUE)
endforeach()
