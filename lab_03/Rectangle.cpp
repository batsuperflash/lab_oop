// #include "Rectangle.h"
// #include <iostream>

// // ввод ширины и высоты
// void Rectangle::read(std::istream& in) {
//     std::cout << "enter width and height: ";
//     in >> width >> height;
// }

// // вывод прямоугольника
// void Rectangle::print(std::ostream& out) const {
//     out << "rectangle: width=" << width << ", height=" << height;
// }

// // вычисление центра
// Point Rectangle::center() const {
//     return { width / 2.0, height / 2.0 };
// }

// // вычисление площади
// double Rectangle::area() const {
//     return width * height;
// }

// // сравнение прямоугольников
// bool Rectangle::operator==(const Figure& other) const {
//     const Rectangle* o = dynamic_cast<const Rectangle*>(&other);
//     return o && width == o->width && height == o->height;
// }


#include "Rectangle.h"
#include <iostream>

// конструктор по умолчанию, создаёт прямоугольник с нулевыми размерами
Rectangle::Rectangle() : width(0), height(0) {}

// конструктор с параметрами
Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

// конструктор копирования
Rectangle::Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}

// оператор присваивания копированием
Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) { // проверка на самоприсваивание
        width = other.width;
        height = other.height;
    }
    return *this;
}

// конструктор перемещения
Rectangle::Rectangle(Rectangle&& other) noexcept : width(other.width), height(other.height) {}

// оператор присваивания перемещением
Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
    }
    return *this;
}

// деструктор
Rectangle::~Rectangle() = default;

// перегрузка оператора == для сравнения прямоугольников
bool Rectangle::operator==(const Figure& other) const {
    const Rectangle* r = dynamic_cast<const Rectangle*>(&other);
    if (!r) return false; // если other не Rectangle
    return width == r->width && height == r->height;
}

// ввод прямоугольника из потока
void Rectangle::read(std::istream& in) {
    std::cout << "enter width and height: ";
    in >> width >> height;
}

// вывод прямоугольника в поток
void Rectangle::print(std::ostream& out) const {
    out << "Rectangle(width=" << width << ", height=" << height << ")";
}

// вычисление геометрического центра
Point Rectangle::center() const {
    return { width / 2, height / 2 };
}

// вычисление площади
double Rectangle::area() const {
    return width * height;
}

// клонирование фигуры
Figure* Rectangle::clone() const {
    return new Rectangle(*this);
}
