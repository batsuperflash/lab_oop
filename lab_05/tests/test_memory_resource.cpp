#include <gtest/gtest.h>
#include "FixedBlockMemoryResource.h"

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
    
    // Должен использовать тот же блок
    void* ptr2 = pool.allocate(128, 1);
    EXPECT_EQ(ptr1, ptr2);
    
    pool.deallocate(ptr2, 128, 1);
}

TEST(FixedBlockMemoryResource, OutOfMemory) {
    FixedBlockMemoryResource pool(100);
    
    EXPECT_THROW(pool.allocate(150, 1), std::bad_alloc);
}

TEST(FixedBlockMemoryResource, IsEqual) {
    FixedBlockMemoryResource pool1(100);
    FixedBlockMemoryResource pool2(100);
    
    EXPECT_TRUE(pool1.is_equal(pool1));
    EXPECT_FALSE(pool1.is_equal(pool2));
}