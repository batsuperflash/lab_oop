#pragma once
#include "figure.hpp"
#include <cmath>
#include <memory>

template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon(const Point<T>& center, T radius) {
        for (int i = 0; i < 6; ++i) {
            double angle = 2*M_PI/6*i;
            this->vertices_.push_back(std::make_unique<Point<T>>(
                center.x + radius * std::cos(angle),
                center.y + radius * std::sin(angle)
            ));
        }
    }

    Hexagon(const Hexagon& other) : Figure<T>(other) {}
    Hexagon(Hexagon&&) noexcept = default;
    Hexagon& operator=(const Hexagon& other) { Figure<T>::operator=(other); return *this; }
    Hexagon& operator=(Hexagon&&) noexcept = default;
    ~Hexagon() override = default;

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Hexagon<T>>(*this);
    }

    double area() const override {
        const auto& a = *this->vertices_[0];
        const auto& b = *this->vertices_[1];
        const auto& c = *this->vertices_[2];
        const auto& d = *this->vertices_[3];
        const auto& e = *this->vertices_[4];
        const auto& f = *this->vertices_[5];
        return (3 * std::sqrt(3) / 2.0) * std::pow(a.distance_to(b),2); // правильный шестиугольник
    }

    Point<T> centroid() const override {
        double cx = 0, cy = 0;
        for (auto& p : this->vertices_) { cx += p->x; cy += p->y; }
        return Point<T>(cx/6, cy/6);
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: ";
        for (const auto& p : this->vertices_) os << *p << " ";
        os << "Area=" << area() << "\n";
    }

    bool operator==(const Figure<T>& other) const override {
        const Hexagon* h = dynamic_cast<const Hexagon*>(&other);
        if (!h) return false;
        for (int i=0; i<6; ++i)
            if (!(*this->vertices_[i] == *h->vertices_[i])) return false;
        return true;
    }
};
