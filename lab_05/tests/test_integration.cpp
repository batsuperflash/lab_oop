#include <gtest/gtest.h>
#include "Vector.h"
#include "FixedBlockMemoryResource.h"

TEST(Integration, VectorWithCustomMemory) {
    FixedBlockMemoryResource pool(1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    
    Vector<int, decltype(alloc)> vec(alloc);
    
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(Integration, ComplexTypeWithCustomMemory) {
    struct TestStruct {
        std::string name;
        int id;
        double value;
        
        TestStruct(const std::string& n, int i, double v) 
            : name(n), id(i), value(v) {}
    };
    
    FixedBlockMemoryResource pool(2048);
    std::pmr::polymorphic_allocator<TestStruct> alloc(&pool);
    
    Vector<TestStruct, decltype(alloc)> vec(alloc);
    
    vec.emplace_back("test1", 1, 1.1);
    vec.emplace_back("test2", 2, 2.2);
    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0].name, "test1");
    EXPECT_EQ(vec[1].id, 2);
    
    // Проверка итераторов со сложным типом
    auto it = vec.begin();
    EXPECT_EQ(it->name, "test1");
    EXPECT_EQ(it->id, 1);
    ++it;
    EXPECT_EQ(it->name, "test2");
}

TEST(Integration, RuleOfFiveWithCustomMemory) {
    FixedBlockMemoryResource pool(1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    
    Vector<int, decltype(alloc)> vec1(alloc);
    vec1.push_back(1);
    vec1.push_back(2);
    
    // Копирование
    Vector<int, decltype(alloc)> vec2 = vec1;
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    
    // Перемещение
    Vector<int, decltype(alloc)> vec3 = std::move(vec1);
    EXPECT_EQ(vec3.size(), 2);
    EXPECT_TRUE(vec1.empty());
}