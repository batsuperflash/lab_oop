cmake_minimum_required(VERSION 3.15)
project(lab_oop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск GoogleTest
find_package(GTest REQUIRED)

# Основная программа (демо)
add_executable(demo
    src/main.cpp
    src/FixedBlockMemoryResource.cpp
)

# Тесты из all_tests.cpp
add_executable(tests
    tests/all_tests.cpp
    src/FixedBlockMemoryResource.cpp
)

# Include директории
target_include_directories(demo PRIVATE include)
target_include_directories(tests PRIVATE include)

# Связывание с GTest
target_link_libraries(tests GTest::gtest GTest::gtest_main)

# Опционально: отдельные тестовые цели
add_executable(test_memory
    tests/test_memory_resource.cpp
    src/FixedBlockMemoryResource.cpp
)
target_include_directories(test_memory PRIVATE include)
target_link_libraries(test_memory GTest::gtest GTest::gtest_main)

add_executable(test_vector
    tests/test_vector.cpp
    src/FixedBlockMemoryResource.cpp
)
target_include_directories(test_vector PRIVATE include)
target_link_libraries(test_vector GTest::gtest GTest::gtest_main)

add_executable(test_iterators
    tests/test_iterators.cpp
    src/FixedBlockMemoryResource.cpp
)
target_include_directories(test_iterators PRIVATE include)
target_link_libraries(test_iterators GTest::gtest GTest::gtest_main)

add_executable(test_integration
    tests/test_integration.cpp
    src/FixedBlockMemoryResource.cpp
)
target_include_directories(test_integration PRIVATE include)
target_link_libraries(test_integration GTest::gtest GTest::gtest_main)

# Цель для запуска всех тестов
add_custom_target(run_all_tests
    COMMAND tests
    DEPENDS tests
)