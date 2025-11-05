#include "Figure.h"

// перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const Figure& f) {
    f.print(out);   // вызывает виртуальный метод print()
    return out;
}

// перегрузка оператора ввода
std::istream& operator>>(std::istream& in, Figure& f) {
    f.read(in);     // вызывает виртуальный метод read()
    return in;
}
