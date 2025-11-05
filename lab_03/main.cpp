#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"



int main() {
    std::vector<Figure*> figures; // коллекция фигур, храним указатели на фигуры
    int n;

    std::cout << "enter number of figures: ";
    std::cin >> n; // вводим количество фигур

    for (int i = 0; i < n; ++i) { // цикл создаёт каждую фигуру по очереди
        int type;
        std::cout << "select type: 1-rectangle, 2-trapezoid, 3-rhombus: ";
        std::cin >> type; // выбираем тип фигуры
        Figure* f = nullptr;
        if (type == 1) f = new Rectangle(); // создаём прямоугольник
        else if (type == 2) f = new Trapezoid(); // создаём трапецию
        else if (type == 3) f = new Rhombus(); // создаём ромб

        if (f) {
            std::cin >> *f; // вводим параметры фигуры через перегруженный >>
            figures.push_back(f); // добавляем фигуру в коллекцию
        }
    }

    double totalArea = 0;
    for (auto f : figures) { // проходим по всем фигурам в коллекции
        Point c = f->center(); // вычисляем геометрический центр
        std::cout << *f << ", center=(" << c.x << "," << c.y << "), area=" << f->area() << "\n"; // выводим данные
        totalArea += f->area(); // считаем общую площадь
    }
    std::cout << "total area: " << totalArea << "\n"; // выводим общую площадь

    int idx;
    std::cout << "enter index to remove: ";
    std::cin >> idx; // индекс фигуры для удаления
    if (idx >= 0 && idx < figures.size()) { // проверяем корректность индекса
        delete figures[idx]; // освобождаем память фигуры
        figures.erase(figures.begin() + idx); // удаляем указатель из коллекции
    }

    for (auto f : figures) delete f; // освобождаем память оставшихся фигур
}
