// #pragma once //директива, которая защищает файл от повторного включения
// #include <iostream>

// // структура точки
// struct Point {
//     double x;
//     double y;
// };

// // базовый класс фигуры
// class Figure {
// public:
//     virtual ~Figure() = default; //вирт деструктор чтоб при удалении 
//     //через delete указателя Figure* вызывался правильный деструктор наследника

//     // ввод фигуры из потока
//     virtual void read(std::istream& in) = 0;

//     // вывод фигуры в поток
//     virtual void print(std::ostream& out) const = 0;

//     // вычисление геометрического центра
//     virtual Point center() const = 0;

//     // вычисление площади
//     virtual double area() const = 0;

//     // создание копии фигуры
//     virtual Figure* clone() const = 0;

//     // сравнение фигур
//     virtual bool operator==(const Figure& other) const = 0;

//     // перегрузка оператора вывода
//     friend std::ostream& operator<<(std::ostream& out, const Figure& f) {
//         f.print(out);
//         return out;
//     }

//     // перегрузка оператора ввода
//     friend std::istream& operator>>(std::istream& in, Figure& f) {
//         f.read(in);
//         return in;
//     }
// };


#pragma once
#include <iostream>

// структура точки
struct Point {
    double x;
    double y;
};

// базовый класс фигуры
class Figure {
public:
    virtual ~Figure() = default;

    // ввод фигуры из потока
    virtual void read(std::istream& in) = 0;

    // вывод фигуры в поток
    virtual void print(std::ostream& out) const = 0;

    // вычисление геометрического центра 
    virtual Point center() const = 0;

    // вычисление площади
    virtual double area() const = 0;

    // создание копии 
    virtual Figure* clone() const = 0;

    // сравнение фигур
    virtual bool operator==(const Figure& other) const = 0;

    // перегрузка операторов (только объявление)
    friend std::ostream& operator<<(std::ostream& out, const Figure& f);
    friend std::istream& operator>>(std::istream& in, Figure& f);
};
