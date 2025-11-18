#pragma once
#include "VectorIterator.h"
#include <memory_resource>
#include <initializer_list>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <memory>  // для std::allocator_traits

template<typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
    Allocator allocator_;

    void resize(std::size_t new_capacity) {
        // ВАЖНО: используем аллокатор для выделения памяти
        T* new_data = allocator_.allocate(new_capacity);
        
        // Переносим существующие элементы с использованием аллокатора
        for (std::size_t i = 0; i < size_; ++i) {
            try {
                // Используем allocator_traits для конструирования
                std::allocator_traits<Allocator>::construct(
                    allocator_, new_data + i, std::move(data_[i]));
            } catch (...) {
                // В случае исключения уничтожаем уже созданные элементы
                for (std::size_t j = 0; j < i; ++j) {
                    std::allocator_traits<Allocator>::destroy(allocator_, new_data + j);
                }
                allocator_.deallocate(new_data, new_capacity);
                throw;
            }
            // Уничтожаем старый элемент
            std::allocator_traits<Allocator>::destroy(allocator_, data_ + i);
        }
        
        // Освобождаем старую память через аллокатор
        if (data_) {
            allocator_.deallocate(data_, capacity_);
        }
        
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;

    // Конструкторы
    Vector() noexcept : data_(nullptr), size_(0), capacity_(0), allocator_() {}
    
    explicit Vector(const Allocator& alloc) noexcept 
        : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {}
    
    Vector(std::size_t count, const T& value, const Allocator& alloc = Allocator())
        : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
        reserve(count);
        for (std::size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    
    explicit Vector(std::size_t count, const Allocator& alloc = Allocator())
        : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
        reserve(count);
        for (std::size_t i = 0; i < count; ++i) {
            emplace_back();
        }
    }
    
    Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
        : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // Правило пять - ДЕСТРУКТОР
    ~Vector() {
        clear();
        if (data_) {
            allocator_.deallocate(data_, capacity_);
        }
    }
    
    // Правило пять - КОПИРОВАНИЕ
    Vector(const Vector& other)
        : data_(nullptr), size_(0), capacity_(0), allocator_(other.allocator_) {
        reserve(other.size_);
        for (std::size_t i = 0; i < other.size_; ++i) {
            push_back(other.data_[i]);
        }
    }
    
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }
    
    // Правило пять - ПЕРЕМЕЩЕНИЕ
    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), 
          capacity_(other.capacity_), allocator_(std::move(other.allocator_)) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            if (data_) {
                allocator_.deallocate(data_, capacity_);
            }
            
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            allocator_ = std::move(other.allocator_);
            
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(allocator_, other.allocator_);
    }
    
    // Методы доступа
    T& operator[](std::size_t index) noexcept { return data_[index]; }
    const T& operator[](std::size_t index) const noexcept { return data_[index]; }
    
    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("Vector index out of range");
        return data_[index];
    }
    
    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("Vector index out of range");
        return data_[index];
    }
    
    T& front() noexcept { return data_[0]; }
    const T& front() const noexcept { return data_[0]; }
    
    T& back() noexcept { return data_[size_ - 1]; }
    const T& back() const noexcept { return data_[size_ - 1]; }
    
    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }
    
    // Емкость
    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
    
    void reserve(std::size_t new_capacity) {
        if (new_capacity > capacity_) {
            resize(new_capacity);
        }
    }
    
    void shrink_to_fit() {
        if (size_ < capacity_) {
            resize(size_);
        }
    }
    
    // Модификаторы
    void clear() {
        for (std::size_t i = 0; i < size_; ++i) {
            std::allocator_traits<Allocator>::destroy(allocator_, data_ + i);
        }
        size_ = 0;
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator_, data_ + size_, value);
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator_, data_ + size_, std::move(value));
        ++size_;
    }
    
    template<typename... Args>
    T& emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator_, data_ + size_, std::forward<Args>(args)...);
        return data_[size_++];
    }
    
    void pop_back() {
        if (size_ > 0) {
            std::allocator_traits<Allocator>::destroy(allocator_, data_ + --size_);
        }
    }
    
    // Итераторы
    iterator begin() noexcept { return iterator(data_); }
    iterator end() noexcept { return iterator(data_ + size_); }
    
    const_iterator begin() const noexcept { return const_iterator(data_); }
    const_iterator end() const noexcept { return const_iterator(data_ + size_); }
    
    const_iterator cbegin() const noexcept { return const_iterator(data_); }
    const_iterator cend() const noexcept { return const_iterator(data_ + size_); }
};