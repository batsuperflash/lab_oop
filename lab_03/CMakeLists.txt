# cmake_minimum_required(VERSION 3.10)
# project(Lab03_OOP)

# set(CMAKE_CXX_STANDARD 17)

# # собираем основное приложение
# add_executable(Lab03_OOP
#     main.cpp
#     Figure.cpp
#     Rectangle.cpp
#     Trapezoid.cpp
#     Rhombus.cpp
# )

# # подключаем google test для тестов
# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # собираем тесты
# add_executable(tests
#     tests/test_figures.cpp
#     Rectangle.cpp
#     Trapezoid.cpp
#     Rhombus.cpp
# )

# target_link_libraries(tests GTest::GTest GTest::Main)
# add_test(NAME AllTests COMMAND tests)

cmake_minimum_required(VERSION 3.10)
project(Lab03_OOP)

# использовать стандарт c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# исходники основной программы
set(SOURCES
    main.cpp
    Figure.cpp
    Rectangle.cpp
    Trapezoid.cpp
    Rhombus.cpp
)

# создаём основной исполняемый файл lab03_oop
add_executable(Lab03_OOP ${SOURCES})

# находим библиотеку gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})  # подключаем заголовки gtest

# создаём исполняемый файл для тестов
add_executable(FigureTests
    tests/test_figures.cpp   # наш тестовый файл
    Figure.cpp
    Rectangle.cpp
    Trapezoid.cpp
    Rhombus.cpp
)

# линкуем gtest и pthread с тестовым исполняемым файлом
target_link_libraries(FigureTests ${GTEST_LIBRARIES} pthread)

# включаем поддержку ctest
enable_testing()

# добавляем тест, который будет запускать all tests
add_test(NAME AllTests COMMAND FigureTests)
