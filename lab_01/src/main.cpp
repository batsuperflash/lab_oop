#include <iostream>
#include <string>
#include "functions.h"


//
//
int main() {
    std::string input;
    std::cout << "enter a string: ";
    std::getline(std::cin, input);

    int vowels = countVowels(input);
    std::cout << "kolvo of vowels: " << vowels << std::endl;
//
    return 0;
}
