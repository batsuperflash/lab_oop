#pragma once
#include "figure.hpp"
#include <cmath>
#include <memory>

// правильный восьмиугольник, вписанный в окружность
template<Scalar T>
class Octagon : public Figure<T> {
public:
    // конструктор: центр + радиус вписанной окружности
    Octagon(const Point<T>& center, T radius) {
        for (int i = 0; i < 8; ++i) {
            double angle = 2 * M_PI / 8 * i; // угол для вершины
            this->vertices_.push_back(std::make_unique<Point<T>>(
                center.x + radius * std::cos(angle),
                center.y + radius * std::sin(angle)
            ));
        }
    }

    // конструктор копирования (deep copy)
    Octagon(const Octagon& other) : Figure<T>(other) {}
    Octagon(Octagon&&) noexcept = default;

    Octagon& operator=(const Octagon& other) { Figure<T>::operator=(other); return *this; }
    Octagon& operator=(Octagon&&) noexcept = default;
    ~Octagon() override = default;

    // клонирование для полиморфизма
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Octagon<T>>(*this);
    }

    // вычисляем площадь правильного восьмиугольника через длину стороны
    double area() const override {
        const auto& a = *this->vertices_[0];
        const auto& b = *this->vertices_[1];
        double side = a.distance_to(b);
        return 2 * (1 + std::sqrt(2)) * side * side; // формула площади правильного восьмиугольника
    }

    // вычисляем геометрический центр (centroid)
    Point<T> centroid() const override {
        double cx = 0, cy = 0;
        for (auto& p : this->vertices_) { cx += p->x; cy += p->y; }
        return Point<T>(cx / 8, cy / 8);
    }

    // вывод координат вершин и площади
    void print(std::ostream& os) const override {
        os << "Octagon: ";
        for (const auto& p : this->vertices_) os << *p << " ";
        os << "Area=" << area() << "\n";
    }

    // сравнение двух восьмиугольников
    bool operator==(const Figure<T>& other) const override {
        const Octagon* o = dynamic_cast<const Octagon*>(&other);
        if (!o) return false;
        for (int i = 0; i < 8; ++i)
            if (!(*this->vertices_[i] == *o->vertices_[i])) return false;
        return true;
    }
};
