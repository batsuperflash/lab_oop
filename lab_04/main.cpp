#include <iostream>
#include <memory>
#include "array.hpp"
#include "triangle.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"

int main() {
    // создаем массив фигур
    Array<std::shared_ptr<Figure<double>>> arr;

    int choice;
    std::cout << "сколько фигур хотите добавить? ";
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cout << "\nвыберите фигуру (1-треугольник, 2-шестиугольник, 3-восьмиугольник): ";
        std::cin >> choice;

        if (choice == 1) {
            double x1, y1, x2, y2, x3, y3;
            std::cout << "введите координаты 3-х вершин через пробел (x y): ";
            std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            arr.push_back(std::make_shared<Triangle<double>>(Point<double>{x1,y1}, Point<double>{x2,y2}, Point<double>{x3,y3}));
        } 
        else if (choice == 2) {
            double cx, cy, r;
            std::cout << "введите центр (x y) и радиус шестиугольника: ";
            std::cin >> cx >> cy >> r;
            arr.push_back(std::make_shared<Hexagon<double>>(Point<double>{cx,cy}, r));
        } 
        else if (choice == 3) {
            double cx, cy, r;
            std::cout << "введите центр (x y) и радиус восьмиугольника: ";
            std::cin >> cx >> cy >> r;
            arr.push_back(std::make_shared<Octagon<double>>(Point<double>{cx,cy}, r));
        } 
        else {
            std::cout << "неверный выбор, фигура не добавлена\n";
            --i; // повторить попытку
        }
    }

    // вывод всех фигур
    std::cout << "\nвсе фигуры:\n";
    for (size_t i = 0; i < arr.size(); ++i) arr[i]->print(std::cout);

    // общая площадь
    std::cout << "total area: " << arr.total_area() << "\n";

    // пример удаления фигуры
    std::cout << "введите индекс фигуры для удаления (0-" << arr.size()-1 << "): ";
    size_t idx;
    std::cin >> idx;
    if (idx < arr.size()) arr.remove_at(idx);

    std::cout << "после удаления:\n";
    for (size_t i = 0; i < arr.size(); ++i) arr[i]->print(std::cout);
}
