cmake_minimum_required(VERSION 3.10)
project(BinaryLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Заголовки
include_directories(include)

# Исходники основного проекта
add_executable(BinaryMain main.cpp src/binary.cpp)

# Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Тесты
add_executable(BinaryTests tests/test_binary.cpp src/binary.cpp)
target_link_libraries(BinaryTests ${GTEST_LIBRARIES} pthread)
add_test(NAME BinaryTests COMMAND BinaryTests)
