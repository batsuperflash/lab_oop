// #pragma once
// #include "Figure.h"

// // класс трапеция
// class Trapezoid : public Figure {
// private:
//     double a, b, h;
// public:
//     Trapezoid() : a(0), b(0), h(0) {}
//     Trapezoid(double a_, double b_, double h_) : a(a_), b(b_), h(h_) {}

//     void read(std::istream& in) override;
//     void print(std::ostream& out) const override;
//     Point center() const override;
//     double area() const override;

//     Figure* clone() const override { return new Trapezoid(*this); }
//     bool operator==(const Figure& other) const override;
// };

#pragma once
#include "Figure.h"

// класс трапеция, наследуется от Figure
class Trapezoid : public Figure {
private:
    double a; // верхнее основание
    double b; // нижнее основание
    double h; // высота
public:
    Trapezoid();                              // конструктор по умолчанию
    Trapezoid(double base1, double base2, double height); // конструктор с параметрами
    Trapezoid(const Trapezoid& other);        // конструктор копирования
    Trapezoid& operator=(const Trapezoid& other); // оператор присваивания копированием
    Trapezoid(Trapezoid&& other) noexcept;        // конструктор перемещения
    Trapezoid& operator=(Trapezoid&& other) noexcept; // оператор присваивания перемещением
    ~Trapezoid() override;                     // деструктор

    bool operator==(const Figure& other) const override; // сравнение двух трапеций

    void read(std::istream& in) override;        // ввод трапеции
    void print(std::ostream& out) const override; // вывод трапеции
    Point center() const override;              // вычисление геометрического центра
    double area() const override;               // вычисление площади
    Figure* clone() const override;             // клонирование фигуры
};
