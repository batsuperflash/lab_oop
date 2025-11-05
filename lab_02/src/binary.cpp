#include "binary.h"
#include <algorithm>

//Конструкторы 
Binary::Binary() : len(0), bits(nullptr) {}

Binary::Binary(size_t n, unsigned char value) : len(n) {
    if (value != 0 && value != 1) throw std::invalid_argument("0 or 1 only");
    bits = new unsigned char[len];
    for (size_t i = 0; i < len; ++i) bits[i] = value;
}

Binary::Binary(const std::string& s) : len(s.size()) {
    bits = new unsigned char[len];
    for (size_t i = 0; i < len; ++i) {
        char c = s[len - 1 - i]; // младший бит = индекс 0
        if (c == '0') bits[i] = 0;
        else if (c == '1') bits[i] = 1;
        else throw std::invalid_argument("0 or 1 only");
    }
}

Binary::Binary(const Binary& other) : len(other.len) {
    bits = new unsigned char[len];
    for (size_t i = 0; i < len; ++i) bits[i] = other.bits[i];
}

Binary::Binary(Binary&& other) noexcept : len(other.len), bits(other.bits) {
    other.bits = nullptr;
    other.len = 0;
}

Binary::~Binary() {
    delete[] bits;
}

// Методы доступа 
size_t Binary::size() const { return len; }

unsigned char Binary::at(size_t i) const {
    if (i >= len) throw std::out_of_range("Index out of range");
    return bits[i];
}

Binary Binary::copy() const { return Binary(*this); }

// Арифметика
Binary Binary::add(const Binary& other) const {
    size_t maxLen = std::max(len, other.len);
    unsigned char* res = new unsigned char[maxLen + 1];
    unsigned char carry = 0;

    for (size_t i = 0; i < maxLen; ++i) {
        unsigned char a = (i < len) ? bits[i] : 0;
        unsigned char b = (i < other.len) ? other.bits[i] : 0;
        unsigned char s = a + b + carry;
        res[i] = s % 2;
        carry = s / 2;
    }
    res[maxLen] = carry;

    Binary r;
    r.len = maxLen + (carry ? 1 : 0);
    r.bits = new unsigned char[r.len];
    for (size_t i = 0; i < r.len; ++i) r.bits[i] = res[i];
    delete[] res;
    return r;
}

Binary Binary::subtract(const Binary& other) const {
    if (this->less(other)) throw std::underflow_error("Negative result");

    unsigned char* res = new unsigned char[len];
    unsigned char borrow = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char a = bits[i];
        unsigned char b = (i < other.len) ? other.bits[i] : 0;
        if (a < b + borrow) {
            res[i] = a + 2 - (b + borrow);
            borrow = 1;
        } else {
            res[i] = a - b - borrow;
            borrow = 0;
        }
    }
    size_t newLen = len;
    while (newLen > 1 && res[newLen - 1] == 0) --newLen;

    Binary r;
    r.len = newLen;
    r.bits = new unsigned char[newLen];
    for (size_t i = 0; i < newLen; ++i) r.bits[i] = res[i];
    delete[] res;
    return r;
}

//  Сравнение 
bool Binary::equals(const Binary& other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; ++i) if (bits[i] != other.bits[i]) return false;
    return true;
}

bool Binary::greater(const Binary& other) const {
    for (size_t i = 0; i < std::max(len, other.len); ++i) {
        unsigned char a = (i < len) ? bits[len - 1 - i] : 0;
        unsigned char b = (i < other.len) ? other.bits[other.len - 1 - i] : 0;
        if (a > b) return true;
        if (a < b) return false;
    }
    return false;
}

bool Binary::less(const Binary& other) const {
    return !greater(other) && !equals(other);
}

// В строку
std::string Binary::toString() const {
    std::string s;
    for (size_t i = 0; i < len; ++i) s = static_cast<char>(bits[i] + '0') + s;
    return s;
}
