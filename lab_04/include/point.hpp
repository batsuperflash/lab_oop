#pragma once
#include <concepts>
#include <cmath>
#include <iostream>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
struct Point {
    T x{};
    T y{};

    Point() = default;
    Point(T x_, T y_) : x(x_), y(y_) {}

    Point(const Point&) = default;
    Point(Point&&) noexcept = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) noexcept = default;
    ~Point() = default;

    bool operator==(const Point& other) const noexcept {
        return x == other.x && y == other.y;
    }

    double distance_to(const Point& other) const {
        double dx = static_cast<double>(x) - static_cast<double>(other.x);
        double dy = static_cast<double>(y) - static_cast<double>(other.y);
        return std::sqrt(dx * dx + dy * dy);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};
