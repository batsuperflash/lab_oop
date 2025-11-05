// #include "Trapezoid.h"
// #include <iostream>

// // ввод параметров трапеции
// void Trapezoid::read(std::istream& in) {
//     std::cout << "enter top base, bottom base and height: ";
//     in >> a >> b >> h;
// }

// // вывод трапеции
// void Trapezoid::print(std::ostream& out) const {
//     out << "trapezoid: a=" << a << ", b=" << b << ", h=" << h;
// }

// // вычисление центра
// Point Trapezoid::center() const {
//     return { (b - a) / 2.0, h / 2.0 };
// }

// // вычисление площади
// double Trapezoid::area() const {
//     return (a + b) * h / 2.0;
// }

// // сравнение трапеций
// bool Trapezoid::operator==(const Figure& other) const {
//     const Trapezoid* o = dynamic_cast<const Trapezoid*>(&other);
//     return o && a == o->a && b == o->b && h == o->h;
// }


#include "Trapezoid.h"
#include <iostream>

// конструктор по умолчанию, трапеция с нулевыми сторонами и высотой
Trapezoid::Trapezoid() : a(0), b(0), h(0) {}

// конструктор с параметрами
Trapezoid::Trapezoid(double base1, double base2, double height) : a(base1), b(base2), h(height) {}

// конструктор копирования
Trapezoid::Trapezoid(const Trapezoid& other) : a(other.a), b(other.b), h(other.h) {}

// оператор присваивания копированием
Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) { // проверка на самоприсваивание
        a = other.a;
        b = other.b;
        h = other.h;
    }
    return *this;
}

// конструктор перемещения
Trapezoid::Trapezoid(Trapezoid&& other) noexcept : a(other.a), b(other.b), h(other.h) {}

// оператор присваивания перемещением
Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        a = other.a;
        b = other.b;
        h = other.h;
    }
    return *this;
}

// деструктор
Trapezoid::~Trapezoid() = default;

// перегрузка оператора == для сравнения трапеций
bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* t = dynamic_cast<const Trapezoid*>(&other);
    if (!t) return false; // если other не трапеция
    return a == t->a && b == t->b && h == t->h;
}

// ввод трапеции из потока
void Trapezoid::read(std::istream& in) {
    std::cout << "enter base a, base b and height: ";
    in >> a >> b >> h;
}

// вывод трапеции в поток
void Trapezoid::print(std::ostream& out) const {
    out << "Trapezoid(a=" << a << ", b=" << b << ", h=" << h << ")";
}

// вычисление геометрического центра
Point Trapezoid::center() const {
    return { (a + b) / 4, h / 2 };
}

// вычисление площади
double Trapezoid::area() const {
    return (a + b) * h / 2;
}

// клонирование фигуры
Figure* Trapezoid::clone() const {
    return new Trapezoid(*this);
}
