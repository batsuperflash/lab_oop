#include "gtest/gtest.h"
#include "../include/binary.h"

// Тест сложения
TEST(BinaryTest, AddTest) {
    Binary a("1011");  // 11
    Binary b("0011");  // 3
    Binary sum = a.add(b);
    EXPECT_EQ(sum.toString(), "1110"); // 14
}

// Тест вычитания
TEST(BinaryTest, SubtractTest) {
    Binary a("1011");
    Binary b("0011");
    Binary diff = a.subtract(b);
    EXPECT_EQ(diff.toString(), "1000"); // 8
}

// Тест сравнения
TEST(BinaryTest, CompareTest) {
    Binary a("1011");
    Binary b("0011");
    EXPECT_TRUE(a.greater(b));
    EXPECT_FALSE(a.less(b));
    EXPECT_FALSE(a.equals(b));
}

// Тест копирования
TEST(BinaryTest, CopyTest) {
    Binary a("1011");
    Binary c = a.copy();
    EXPECT_TRUE(a.equals(c));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
