// #pragma once
// #include "Figure.h"

// // класс ромб
// class Rhombus : public Figure {
// private:
//     double d1, d2;
// public:
//     Rhombus() : d1(0), d2(0) {}
//     Rhombus(double d1_, double d2_) : d1(d1_), d2(d2_) {}

//     void read(std::istream& in) override;
//     void print(std::ostream& out) const override;
//     Point center() const override;
//     double area() const override;

//     Figure* clone() const override { return new Rhombus(*this); }
//     bool operator==(const Figure& other) const override;
// };

#pragma once
#include "Figure.h"

// класс ромб, наследуется от Figure
class Rhombus : public Figure {
private:
    double d1; // первая диагональ
    double d2; // вторая диагональ
public:
    Rhombus();                             // конструктор по умолчанию
    Rhombus(double diag1, double diag2);   // конструктор с параметрами
    Rhombus(const Rhombus& other);         // конструктор копирования
    Rhombus& operator=(const Rhombus& other); // оператор присваивания копированием
    Rhombus(Rhombus&& other) noexcept;        // конструктор перемещения
    Rhombus& operator=(Rhombus&& other) noexcept; // оператор присваивания перемещением
    ~Rhombus() override;                    // деструктор

    bool operator==(const Figure& other) const override; // сравнение двух ромбов

    void read(std::istream& in) override;       // ввод ромба
    void print(std::ostream& out) const override; // вывод ромба
    Point center() const override;             // вычисление геометрического центра
    double area() const override;              // вычисление площади
    Figure* clone() const override;            // клонирование фигуры
};
