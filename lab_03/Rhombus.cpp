// #include "Rhombus.h"
// #include <iostream>

// // ввод диагоналей
// void Rhombus::read(std::istream& in) {
//     std::cout << "enter diagonals: ";
//     in >> d1 >> d2;
// }

// // вывод ромба
// void Rhombus::print(std::ostream& out) const {
//     out << "rhombus: d1=" << d1 << ", d2=" << d2;
// }

// // центр ромба
// Point Rhombus::center() const {
//     return { d1 / 2.0, d2 / 2.0 };
// }

// // площадь ромба
// double Rhombus::area() const {
//     return d1 * d2 / 2.0;
// }

// // сравнение ромбов
// bool Rhombus::operator==(const Figure& other) const {
//     const Rhombus* o = dynamic_cast<const Rhombus*>(&other);
//     return o && d1 == o->d1 && d2 == o->d2;
// }


#include "Rhombus.h"
#include <iostream>

// конструктор по умолчанию, ромб с нулевыми диагоналями
Rhombus::Rhombus() : d1(0), d2(0) {}

// конструктор с параметрами
Rhombus::Rhombus(double diag1, double diag2) : d1(diag1), d2(diag2) {}

// конструктор копирования
Rhombus::Rhombus(const Rhombus& other) : d1(other.d1), d2(other.d2) {}

// оператор присваивания копированием
Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) { // проверка на самоприсваивание
        d1 = other.d1;
        d2 = other.d2;
    }
    return *this;
}

// конструктор перемещения
Rhombus::Rhombus(Rhombus&& other) noexcept : d1(other.d1), d2(other.d2) {}

// оператор присваивания перемещением
Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        d1 = other.d1;
        d2 = other.d2;
    }
    return *this;
}

// деструктор
Rhombus::~Rhombus() = default;

// перегрузка оператора == для сравнения ромбов
bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* r = dynamic_cast<const Rhombus*>(&other);
    if (!r) return false; // если other не ромб
    return d1 == r->d1 && d2 == r->d2;
}

// ввод ромба из потока
void Rhombus::read(std::istream& in) {
    std::cout << "enter diagonals d1 and d2: ";
    in >> d1 >> d2;
}

// вывод ромба в поток
void Rhombus::print(std::ostream& out) const {
    out << "Rhombus(d1=" << d1 << ", d2=" << d2 << ")";
}

// вычисление геометрического центра
Point Rhombus::center() const {
    return { d1 / 2, d2 / 2 };
}

// вычисление площади
double Rhombus::area() const {
    return d1 * d2 / 2;
}

// клонирование фигуры
Figure* Rhombus::clone() const {
    return new Rhombus(*this);
}
