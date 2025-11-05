#pragma once
#include "figure.hpp"
#include <cmath>
#include <memory>

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        this->vertices_.push_back(std::make_unique<Point<T>>(a));
        this->vertices_.push_back(std::make_unique<Point<T>>(b));
        this->vertices_.push_back(std::make_unique<Point<T>>(c));
    }

    Triangle(const Triangle& other) : Figure<T>(other) {}
    Triangle(Triangle&&) noexcept = default;
    Triangle& operator=(const Triangle& other) { Figure<T>::operator=(other); return *this; }
    Triangle& operator=(Triangle&&) noexcept = default;
    ~Triangle() override = default;

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Triangle<T>>(*this);
    }

    double area() const override {
        const auto& a = *this->vertices_[0];
        const auto& b = *this->vertices_[1];
        const auto& c = *this->vertices_[2];
        return std::abs((a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))/2.0);
    }

    Point<T> centroid() const override {
        const auto& a = *this->vertices_[0];
        const auto& b = *this->vertices_[1];
        const auto& c = *this->vertices_[2];
        return Point<T>((a.x+b.x+c.x)/3, (a.y+b.y+c.y)/3);
    }

    void print(std::ostream& os) const override {
        os << "Triangle: ";
        for (const auto& p : this->vertices_) os << *p << " ";
        os << "Area=" << area() << "\n";
    }

    bool operator==(const Figure<T>& other) const override {
        const Triangle* t = dynamic_cast<const Triangle*>(&other);
        if (!t) return false;
        for (int i=0; i<3; ++i)
            if (!(*this->vertices_[i] == *t->vertices_[i])) return false;
        return true;
    }
};
