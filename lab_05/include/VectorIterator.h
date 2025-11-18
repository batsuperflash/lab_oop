#pragma once
#include <iterator>

template<typename T>
class VectorIterator {
private:
    T* current_ptr;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // Конструкторы
    VectorIterator() noexcept : current_ptr(nullptr) {}
    explicit VectorIterator(T* ptr) noexcept : current_ptr(ptr) {}
    
    // Правило пяти
    ~VectorIterator() = default;
    VectorIterator(const VectorIterator&) = default;
    VectorIterator& operator=(const VectorIterator&) = default;
    VectorIterator(VectorIterator&&) noexcept = default;
    VectorIterator& operator=(VectorIterator&&) noexcept = default;
    
    // Операторы доступа
    reference operator*() const noexcept { return *current_ptr; }
    pointer operator->() const noexcept { return current_ptr; }
    
    // Инкремент
    VectorIterator& operator++() noexcept {
        ++current_ptr;
        return *this;
    }
    
    VectorIterator operator++(int) noexcept {
        VectorIterator temp = *this;
        ++current_ptr;
        return temp;
    }
    
    // Сравнение
    bool operator==(const VectorIterator& other) const noexcept {
        return current_ptr == other.current_ptr;
    }
    
    bool operator!=(const VectorIterator& other) const noexcept {
        return current_ptr != other.current_ptr;
    }
};