include(FetchContent) #подкл модуль FetchContent  чтоб скачать GoogleTest прям при сборке

# пробую подключить googletest 
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)   #делает библиотеку доступной

# инклуды 
include_directories(${CMAKE_SOURCE_DIR}/src) #добавляет хедеры из src
# include_directories(include) # вариант

# тестовый исполняемый файл
add_executable(tests 
    test_functions.cpp 
    ../src/functions.cpp   # тащу прямо cpp
)


# линковка с gtest
target_link_libraries(tests gtest_main) 
# 
include(GoogleTest)
gtest_discover_tests(tests) 