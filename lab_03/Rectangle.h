// #pragma once
// #include "Figure.h"

// // класс прямоугольник
// class Rectangle : public Figure {
// private:
//     double width;
//     double height;
// public:
//     Rectangle() : width(0), height(0) {}
//     Rectangle(double w, double h) : width(w), height(h) {}

//     void read(std::istream& in) override;
//     void print(std::ostream& out) const override;
//     Point center() const override;
//     double area() const override;

//     Figure* clone() const override { return new Rectangle(*this); }
//     bool operator==(const Figure& other) const override;
// };
#pragma once
#include "Figure.h"

// класс прямоугольник, наследуется от Figure
class Rectangle : public Figure {
private:
    double width;  // ширина прямоугольника
    double height; // высота прямоугольника
public:
    Rectangle();                           // конструктор по умолчанию
    Rectangle(double w, double h);         // конструктор с параметрами
    Rectangle(const Rectangle& other);     // конструктор копирования
    Rectangle& operator=(const Rectangle& other); // оператор присваивания копированием
    Rectangle(Rectangle&& other) noexcept;        // конструктор перемещения
    Rectangle& operator=(Rectangle&& other) noexcept; // оператор присваивания перемещением
    ~Rectangle() override;                  // деструктор

    bool operator==(const Figure& other) const override; // сравнение двух фигур

    void read(std::istream& in) override;               // ввод фигуры
    void print(std::ostream& out) const override;      // вывод фигуры
    Point center() const override;                      // вычисление геометрического центра
    double area() const override;                       // вычисление площади
    Figure* clone() const override;                     // клонирование фигуры
};
