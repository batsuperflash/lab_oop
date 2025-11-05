#pragma once
#include <memory>
#include <utility>

// простой шаблонный динамический массив
template<typename T>
class Array {
    std::unique_ptr<T[]> data_; // данные
    std::size_t size_ = 0;      // тек размер
    std::size_t capacity_ = 4;  // емкость

public:
    Array() { data_ = std::make_unique<T[]>(capacity_); }

    // копирование
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::make_unique<T[]>(capacity_);
        for (size_t i=0;i<size_;++i) data_[i] = other.data_[i]; // копируем элементы
    }

    Array(Array&&) noexcept = default;
    Array& operator=(const Array& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = std::make_unique<T[]>(capacity_);
            for (size_t i=0;i<size_;++i) data_[i] = other.data_[i]; // копируем
        }
        return *this;
    }

    Array& operator=(Array&&) noexcept = default;
    ~Array() = default;

    // добавляем элемент
    void push_back(T value) {
        if (size_ == capacity_) resize();     // увеличиваем емкость если нужно
        data_[size_++] = std::move(value);    // перемещаем элемент
    }

    // удаляем по индексу
    void remove_at(std::size_t idx) {
        if (idx >= size_) return;
        for (std::size_t i=idx;i<size_-1;++i)
            data_[i] = std::move(data_[i+1]); // сдвигаем элементы
        --size_;
    }

    // доступ по индексу
    T& operator[](std::size_t idx) { return data_[idx]; }
    const T& operator[](std::size_t idx) const { return data_[idx]; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }

    // считаем суммарную площадь (для фигур с operator double)
    double total_area() const {
    double sum = 0;
    for (std::size_t i=0;i<size_;++i)
        sum += static_cast<double>(*data_[i]); // разыменовываем shared_ptr
    return sum;
    }



private:
    // увеличиваем емкость массива
    void resize() {
        capacity_ *= 2; // удваиваем
        auto new_data = std::make_unique<T[]>(capacity_);
        for (std::size_t i=0;i<size_;++i) new_data[i] = std::move(data_[i]);
        data_ = std::move(new_data);
    }
};
