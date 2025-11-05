

#include "functions.h"
#include <gtest/gtest.h>

// тест пустой строки, -> 0 
TEST(CountVowelsTest, EmptyString) {
EXPECT_EQ(countVowels(""), 0);  // проверяет, что реальный результат равен ожидаемому
}

//  вообще без гласных
TEST(CountVowelsTest, NoVowels) {
    EXPECT_EQ(countVowels("bcdfg"), 0); 
    // EXPECT_EQ(countVowels("zzz"), 0); // 
}

// все символы гласные
TEST(CountVowelsTest, OnlyVowels) 
{
 EXPECT_EQ(countVowels("aeiouy"), 6); // 6 
}

// смешанная строка
TEST(CountVowelsTest, MixedString) {
    auto res = countVowels("hello world");
    EXPECT_EQ(res, 3); // e, o, o
    // EXPECT_EQ(countVowels("hello world"), 3);
}
//