#include "FixedBlockMemoryResource.h"
#include <new>
#include <stdexcept>
#include <algorithm>

BlockInfo::BlockInfo(void* addr, std::size_t sz, bool occupied)
    : address(addr), size(sz), is_occupied(occupied) {}

FixedBlockMemoryResource::FixedBlockMemoryResource(std::size_t size) 
    : total_size(size) {
    big_block = ::operator new(size);
    block_list.emplace_back(big_block, size, false);
    std::cout << "FixedBlockMemoryResource created with " << size << " bytes\n";
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    // Проверяем на утечки
    bool has_leaks = false;
    for (const auto& block : block_list) {
        if (block.is_occupied) {
            has_leaks = true;
            std::cerr << "Memory leak detected: block at " << block.address 
                      << " size " << block.size << " bytes\n";
        }
    }
    
    ::operator delete(big_block);
    if (!has_leaks) {
        std::cout << "FixedBlockMemoryResource destroyed cleanly\n";
    }
}

void* FixedBlockMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    // Ищем первый подходящий свободный блок
    for (auto it = block_list.begin(); it != block_list.end(); ++it) {
        if (!it->is_occupied && it->size >= bytes) {
            // Если блок больше нужного - разделяем его
            if (it->size > bytes) {
                void* remaining_addr = static_cast<char*>(it->address) + bytes;
                std::size_t remaining_size = it->size - bytes;
                
                block_list.insert(std::next(it), 
                    BlockInfo(remaining_addr, remaining_size, false));
                it->size = bytes;
            }
            
            it->is_occupied = true;
            std::cout << "Allocated " << bytes << " bytes at " << it->address << "\n";
            return it->address;
        }
    }
    throw std::bad_alloc();
}

void FixedBlockMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    // Находим блок по указателю
    for (auto it = block_list.begin(); it != block_list.end(); ++it) {
        if (it->address == p && it->is_occupied) {
            it->is_occupied = false;
            std::cout << "Deallocated " << bytes << " bytes at " << p << "\n";
            
            // Попробуем объединить с соседними свободными блоками
            auto next_it = std::next(it);
            if (next_it != block_list.end() && !next_it->is_occupied) {
                it->size += next_it->size;
                block_list.erase(next_it);
            }
            
            if (it != block_list.begin()) {
                auto prev_it = std::prev(it);
                if (!prev_it->is_occupied) {
                    prev_it->size += it->size;
                    block_list.erase(it);
                }
            }
            return;
        }
    }
    throw std::runtime_error("Attempt to deallocate invalid pointer");
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

FixedBlockMemoryResource::FixedBlockMemoryResource(FixedBlockMemoryResource&& other) noexcept
    : big_block(other.big_block), total_size(other.total_size), 
      block_list(std::move(other.block_list)) {
    other.big_block = nullptr;
    other.total_size = 0;
}

FixedBlockMemoryResource& FixedBlockMemoryResource::operator=(FixedBlockMemoryResource&& other) noexcept {
    if (this != &other) {
        // Освобождаем текущие ресурсы
        if (big_block) {
            ::operator delete(big_block);
        }
        
        big_block = other.big_block;
        total_size = other.total_size;
        block_list = std::move(other.block_list);
        
        other.big_block = nullptr;
        other.total_size = 0;
    }
    return *this;
}

void FixedBlockMemoryResource::print_blocks() const {
    std::cout << "Memory blocks:\n";
    for (const auto& block : block_list) {
        std::cout << "  Addr: " << block.address << " Size: " << block.size 
                  << " Status: " << (block.is_occupied ? "OCCUPIED" : "FREE") << "\n";
    }
}