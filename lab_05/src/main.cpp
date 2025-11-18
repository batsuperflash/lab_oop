#include <iostream>
#include <string>
#include "FixedBlockMemoryResource.h"
#include "Vector.h"

// Сложный тип для демонстрации (БЕЗ отладочного вывода)
struct Person {
    std::string name;
    int age;
    double salary;
    
    Person(const std::string& n = "", int a = 0, double s = 0.0) 
        : name(n), age(a), salary(s) {}
    
    // Конструкторы/деструкторы без cout
    Person(const Person& other) = default;
    Person(Person&& other) noexcept = default;
    Person& operator=(const Person& other) = default;
};

void demo_simple_types() {
    std::cout << "\n=== Демонстрация с простыми типами (int) ===\n";
    
    FixedBlockMemoryResource pool(1024); //выделяю блок памяти
    std::pmr::polymorphic_allocator<int> alloc(&pool); //указываю через polymorphic_allocator на него
    Vector<int, decltype(alloc)> numbers(alloc); //создаю структуру для использования этого блока 
    
    // Заполняем вектор
    for (int i = 1; i <= 5; ++i) {
        numbers.push_back(i * 10);
    }
    
    // Демонстрация итераторов
    std::cout << "Элементы через итераторы: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Демонстрация range-based for
    std::cout << "Элементы через range-based for: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    std::cout << "Размер: " << numbers.size() << ", Емкость: " << numbers.capacity() << "\n";
}

void demo_complex_types() {
    std::cout << "\n=== Демонстрация со сложными типами (Person) ===\n";
    
    FixedBlockMemoryResource pool(2048);
    std::pmr::polymorphic_allocator<Person> alloc(&pool);
    Vector<Person, decltype(alloc)> people(alloc);
    
    // Добавляем элементы
    people.emplace_back("Alice", 25, 50000.0);
    people.emplace_back("Bob", 30, 60000.0);
    people.emplace_back("Charlie", 35, 70000.0);
    
    // Итерация с доступом к членам через ->
    std::cout << "Данные людей:\n";
    for (auto it = people.begin(); it != people.end(); ++it) {
        std::cout << "  " << it->name << ", возраст: " << it->age 
                  << ", зарплата: " << it->salary << "\n";
    }
    
    // Демонстрация правила пяти
    std::cout << "\n--- Демонстрация копирования вектора ---\n";
    Vector<Person> people_copy = people;
    
    std::cout << "Оригинал (" << people.size() << " элементов): ";
    for (const auto& p : people) std::cout << p.name << " ";
    std::cout << "\nКопия (" << people_copy.size() << " элементов): ";
    for (const auto& p : people_copy) std::cout << p.name << " ";
    std::cout << "\n";
}

void demo_memory_reuse() {
    std::cout << "\n=== Демонстрация повторного использования памяти ===\n";
    
    FixedBlockMemoryResource pool(256);
    
    std::cout << "Начальное состояние:\n";
    pool.print_blocks();
    
    // Выделяем и освобождаем память несколько раз
    void* ptr1 = pool.allocate(64, 1);
    void* ptr2 = pool.allocate(32, 1);
    
    std::cout << "После выделения двух блоков:\n";
    pool.print_blocks();
    
    pool.deallocate(ptr1, 64, 1);
    std::cout << "После освобождения первого блока:\n";
    pool.print_blocks();
    
    // Память должна быть повторно использована
    void* ptr3 = pool.allocate(50, 1);
    std::cout << "После повторного выделения (должен использовать освобожденный блок):\n";
    pool.print_blocks();
    
    pool.deallocate(ptr2, 32, 1);
    pool.deallocate(ptr3, 50, 1);
}

int main() {
    std::cout << "=== Лабораторная работа: Итераторы и Аллокаторы ===\n";
    
    try {
        demo_simple_types();
        demo_complex_types();
        demo_memory_reuse();
        
        std::cout << "\n=== Все демонстрации завершены успешно ===\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}