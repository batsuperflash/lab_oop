#include <gtest/gtest.h>
#include "Vector.h"

TEST(VectorIterator, BasicOperations) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    // Проверка forward iterator
    auto it = vec.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, vec.end());
    
    // Проверка range-based for
    int sum = 0;
    for (const auto& item : vec) {
        sum += item;
    }
    EXPECT_EQ(sum, 6);
}

TEST(VectorIterator, ConstIterator) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    
    const Vector<int>& const_vec = vec;
    auto it = const_vec.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}