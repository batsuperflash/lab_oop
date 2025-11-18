#include <gtest/gtest.h>
#include "Vector.h"

TEST(Vector, BasicOperations) {
    Vector<int> vec;
    
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
    
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);
}

TEST(Vector, EmplaceBack) {
    Vector<std::string> vec;
    
    vec.emplace_back("hello");
    vec.emplace_back(5, 'a');
    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec[1], "aaaaa");
}