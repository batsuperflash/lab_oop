#include "include/binary.h"
#include <iostream>

int main() {
    try {
        Binary a("1011"); // 11
        Binary b("0011"); // 3

        Binary sum = a.add(b);
        Binary diff = a.subtract(b);

        std::cout << "A: " << a.toString() << std::endl;
        std::cout << "B: " << b.toString() << std::endl;
        std::cout << "A + B = " << sum.toString() << std::endl;
        std::cout << "A - B = " << diff.toString() << std::endl;

        std::cout << "A > B? " << (a.greater(b) ? "Yes" : "No") << std::endl;
        std::cout << "A < B? " << (a.less(b) ? "Yes" : "No") << std::endl;
        std::cout << "A == B? " << (a.equals(b) ? "Yes" : "No") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
