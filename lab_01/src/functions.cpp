


#include "functions.h"

// функция считает сколько гласных в строке (англ буквы)
// мб не идеально

int countVowels(const std::string &stroka) {
 int kolvo = 0;
 for (int i = 0; i < stroka.size(); i++) {
     char b = stroka[i]; // вытаскиваем символ
     // проверка на гласные, не забыла ничего
     if (b == 'a' || b == 'e' || b == 'i' ||
         b == 'o' || b == 'u' || b == 'y') {
         kolvo = kolvo + 1; 
     } else {
         //
     }
 }
 // 
 return kolvo;
}
