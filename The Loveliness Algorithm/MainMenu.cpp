// В КАЖДОМ ЗАДАНИИ НЕОБХОДИМО :
// 1. создать программу на языке С / С++, которая позволяет выбрать номер лабораторной работы семестра(1, 2, 3, 4);
// 2. создать массив объектов указанных классов;
// 3. считать данные объектов с клавиатуры;
// 4. вывести данные объектов на экран и в файл;
// 5. создать методы установки значений полей класса. Методы должны проверять корректность задаваемых параметров;
// 6. создать конструктор с параметрами, конструктор без параметров, конструктор копирования, деструктор.

#include "MyIncludes.h"
#include "HeaderLaba1.h"
#include "HeaderLaba2.h"
#include "HeaderLaba3.h"
#include "HeaderLaba4.h"
#include "HeaderLaba5.h"
#include "HeaderLaba6.h"
#include "HeaderLaba7.h"
#include "HeaderLaba8.h"

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    bool exit = false;

    cout << "Добро пожаловать в главное меню" << endl;

    do {
        cout << "\nМеню лабораторных работ" << endl;
        cout << "1. Классы и объекты" << endl;
        cout << "2. Дружественные функции и классы" << endl;
        cout << "3. Наследование" << endl;
        cout << "4. Полиморфизм, виртуальные функции и абстрактные классы" << endl;
        cout << "5. Множественное и виртуальное наследлвание" << endl;
        cout << "6. Практические приемы использования шаблонов типов и иерархии классов" << endl;
        cout << "7. Практические приемы использования smart-указателей и механизма транзакций" << endl;
        cout << "8. Генерация и обработка исключительных ситуаций" << endl;
        cout << "9. Выйти" << endl << endl;

        cout << "Введите ваш выбор: ";
        while (!(cin >> choice) || choice < 1 || choice > 9) {
            if (choice > 1 && choice < 9) cout << "Пока производится работа по выполнению данной работы, попробуйте позже" << endl;
            cout << "Выберите одну из написанных лабораторных работ: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } cout << endl;

        switch (choice) {
            case 1: Laba1(); break;
            case 2: Laba2(); break;
            case 3: Laba3(); break;
            case 4: Laba4(); break;
            case 5: Laba5(); break;
            case 6: Laba6(); break;
            case 7: Laba7(); break;
            case 8: Laba8(); break;
        case 9:
            bool answer = false;
            cin.ignore();
            cout << "Вы точно уверены, что хотите выйти с проекта? (да/нет): ";
            do {
                string danetka;
                getline(cin, danetka);

                transform(danetka.begin(), danetka.end(), danetka.begin(), ::tolower);
                if (danetka == "да") { exit = true; answer = true; break; }
                else if (danetka == "нет") { exit = false; answer = true; break; }
                else cout << "Выберите только 'да' / 'нет': ";

            } while (!answer); break;
        }

    } while (!exit);
    cout << "Выход из проекта..." << endl;

    return 0;
}