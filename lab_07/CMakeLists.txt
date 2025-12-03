cmake_minimum_required(VERSION 3.10)
project(DungeonRPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(dungeon
    main.cpp
    dungeon.cpp
    NPCtypes.cpp
    NPC.h
    NPCtypes.h
    dungeon.h
)
# ---------------- Google Test ----------------
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests
    tests/test_dungeon.cpp
    dungeon.cpp
    NPCtypes.cpp
    NPC.h
    NPCtypes.h
    dungeon.h
)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
add_test(NAME dungeon_tests COMMAND tests)
