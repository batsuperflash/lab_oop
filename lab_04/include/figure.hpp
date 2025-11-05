#pragma once
#include "point.hpp"
#include <vector>
#include <memory>
#include <iostream>

template<Scalar T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices_;

public:
    Figure() = default;
    Figure(const Figure& other) {
        for (const auto& p : other.vertices_)
            vertices_.push_back(std::make_unique<Point<T>>(*p));
    }
    Figure(Figure&&) noexcept = default;

    Figure& operator=(const Figure& other) {
        if (this != &other) {
            vertices_.clear();
            for (const auto& p : other.vertices_)
                vertices_.push_back(std::make_unique<Point<T>>(*p));
        }
        return *this;
    }
    Figure& operator=(Figure&&) noexcept = default;

    virtual ~Figure() = default;

    virtual std::shared_ptr<Figure<T>> clone() const = 0;
    virtual double area() const = 0;
    virtual Point<T> centroid() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual bool operator==(const Figure& other) const = 0;

    operator double() const { return area(); }

    const std::vector<std::unique_ptr<Point<T>>>& vertices() const { return vertices_; }
};
