#include <gtest/gtest.h>
#include "FixedBlockMemoryResource.h"
#include "Vector.h"

// Тесты для FixedBlockMemoryResource
TEST(FixedBlockMemoryResource, BasicAllocation) {
    FixedBlockMemoryResource pool(1024);
    
    void* ptr1 = pool.allocate(100, 1);
    void* ptr2 = pool.allocate(200, 1);
    
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr1, ptr2);
    
    pool.deallocate(ptr1, 100, 1);
    pool.deallocate(ptr2, 200, 1);
}

TEST(FixedBlockMemoryResource, MemoryReuse) {
    FixedBlockMemoryResource pool(512);
    
    void* ptr1 = pool.allocate(128, 1);
    pool.deallocate(ptr1, 128, 1);
    
    void* ptr2 = pool.allocate(128, 1);
    EXPECT_EQ(ptr1, ptr2);
    
    pool.deallocate(ptr2, 128, 1);
}

// Тесты для Vector
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
}

// Тесты для итераторов
TEST(VectorIterator, BasicOperations) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    auto it = vec.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

// Интеграционные тесты
TEST(Integration, VectorWithCustomMemory) {
    FixedBlockMemoryResource pool(1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Vector<int, decltype(alloc)> vec(alloc);
    
    for (int i = 0; i < 5; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}