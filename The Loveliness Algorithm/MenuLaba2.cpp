//19. Создать класс ArrayFloat, реализующий динамический массив вещественных чисел.В классе создать поле size,
//хранящее размер массива, указатель на массив типа float.Память под массив выделять динамически в конструкторе
//и освобождать в деструкторе.Создать конструктор без параметров, конструктор с двумя параметрами
//ArrayFloat(int, float*) (размер массива и массив), конструктор копирования, деструктор.Создать методы доступа
//к полю size, методы доступа к конкретному элементу массива с заданным индексом, метод отображения массива в
//виде набора строк и столбцов на экран, перегрузить оператор присваивания, которые реализует копирование массивов.
//Реализовать friend - функции для операторов ввода / вывода в поток для созданного класса.

#include "MyIncludes.h"
#include "HeaderLaba2.h"

extern void Laba2() {
    ArrayFloat array;
    int choice;

    do {
        cout << "=== Меню ===" << endl;
        cout << "1. Ввести данные массива" << endl;
        cout << "2. Вывести данные массива в строчном виде (через cout << array)" << endl;
        cout << "3. Вывести данные массива в табличном виде (через array.display())" << endl;
        cout << "4. Сохранить данные в файл" << endl;
        cout << "5. Выгрузить данные из файла" << endl;
        cout << "6. Выйти из программы" << endl;
        cout << "Выберите пункт: ";
        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "Выюерите один из предложенных выше вариантов: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: cin >> array; break;
        case 2: cout << array; break;
        case 3: array.display(); break;
        case 4: saveToFile(array, "array_data.txt"); break;
        case 5: loadFromFile(array, "array_data.txt"); break;
        case 6: cout << "Выход из программы..." << endl; break;
        }
        cout << endl;

    } while (choice != 6);
}