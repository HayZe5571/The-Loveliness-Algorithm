// Построить иерархию классов согласно схеме наследования, приведенной на рисунке ниже по предметной
// области «Книжный магазин». Каждый класс должен содержать необходимые конструкторы и методы работы 
// с полями классов. Функция main() должна иллюстрировать работу с массивами объектов всех созданных
// классов. При необходимости самостоятельно добавить классы для реализации множественного наследования.
//
//                       +-----+
//                       |     |
//                       +-----+
//                      /       \
//               +-----+         +-----+
//               |     |         |     |
//               +-----+         +-----+
//                      \       /
//                       +-----+
//                       |     |
//                       +-----+

#include "MyIncludes.h"
#include "HeaderLaba5.h"

vector<Product*> products;

void Laba5() {
    int choice;

    do {
        cout << "\n========== МЕНЮ ЛАБАРАТОРНОЙ №5 ==========" << endl;
        cout << "1. Добавить товары" << endl;
        cout << "2. Вывести все товары" << endl;
        cout << "3. Сохранить данные в файл" << endl;
        cout << "4. Загрузить данные из файла" << endl;
        cout << "5. Очистить все данные" << endl;
        cout << "6. Выход в главное меню" << endl;

        choice = chekInt("Выберите пункт", "Неверный выбор", [](int x) { return x >= 1 && x <= 6; });

        switch (choice) {
        case 1: addProduct(); break;
        case 2: displayAllProducts(); break;
        case 3: saveToFileProducts("products_data.txt"); break;
        case 4: loadFromFileProducts("products_data.txt"); break;
        case 5: clearProducts(); break;
        case 6: cout << "Возврат в главное меню..." << endl; break;
        }
    } while (choice != 6);
}