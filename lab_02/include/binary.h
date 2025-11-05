#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <stdexcept>

class Binary {
private:
    size_t len;
    unsigned char* bits;

public:
    // Конструкторы и деструктор
    Binary();                     
    Binary(size_t n, unsigned char value = 0); 
    Binary(const std::string& s);
    Binary(const Binary& other);  
    Binary(Binary&& other) noexcept; 
    ~Binary();

    // Методы доступа
    size_t size() const;
    unsigned char at(size_t i) const;

    // Арифметические операции
    Binary add(const Binary& other) const;
    Binary subtract(const Binary& other) const;
    Binary copy() const;

    // Операции сравнения
    bool equals(const Binary& other) const;
    bool greater(const Binary& other) const;
    bool less(const Binary& other) const;

    // Вывод в строку
    std::string toString() const;
};

#endif
