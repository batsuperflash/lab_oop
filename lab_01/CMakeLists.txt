# cmake_minimum_required(VERSION 3.10)
# project(lab_01 LANGUAGES C CXX)

# enable_testing()

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# option(BUILD_TESTS "Build tests" ON)

# add_subdirectory(src)

# if(BUILD_TESTS AND EXISTS ${CMAKE_SOURCE_DIR}/tests)
#   add_subdirectory(tests)
# endif()


cmake_minimum_required(VERSION 3.10)   # 
project(lab_01 LANGUAGES C CXX)  

enable_testing()   # включается поддержка тестов

set(CMAKE_CXX_STANDARD 17)       # хочу стандарт C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) 


option(BUILD_TESTS "Build tests" ON)   #ON но можно собрать проект без тестов

# добав src
add_subdirectory(src)   


if(BUILD_TESTS AND EXISTS ${CMAKE_SOURCE_DIR}/tests)
   add_subdirectory(tests)   # подтягиваем тесты если есть папка
else()
   message(STATUS "tесты пока не собираем")  # чисто чтобы видеть в логах
endif()

