#pragma once
#include <memory_resource>
#include <list>
#include <cstddef>
#include <iostream>

struct BlockInfo {
    void* address;
    std::size_t size;
    bool is_occupied;
    
    BlockInfo(void* addr, std::size_t sz, bool occupied = false);
};

class FixedBlockMemoryResource : public std::pmr::memory_resource {
private:
    void* big_block;
    std::size_t total_size;
    std::list<BlockInfo> block_list;
    
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    explicit FixedBlockMemoryResource(std::size_t size);
    ~FixedBlockMemoryResource();
    
    // Правило пяти - удаляем копирование
    FixedBlockMemoryResource(const FixedBlockMemoryResource&) = delete;
    FixedBlockMemoryResource& operator=(const FixedBlockMemoryResource&) = delete;
    
    // Разрешаем перемещение
    FixedBlockMemoryResource(FixedBlockMemoryResource&& other) noexcept;
    FixedBlockMemoryResource& operator=(FixedBlockMemoryResource&& other) noexcept;
    
    void print_blocks() const;
};