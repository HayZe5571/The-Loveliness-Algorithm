// 19. Создать класс Library (библиотека). Предусмотреть возможность работы с произвольным числом книг в библиотеке,
// поиска книги по какому-либо признаку (например, по автору или по году издания), добавления книг в библиотеку,
// удаления книг из нее. В класс добавить необходимый набор полей и методов (минимум два поля и два метода) на свое усмотрение.

#include "MyIncludes.h"
#include "HeaderLaba1.h"

extern void Laba1() {
    vector<Library> books;
    int choice, kolvoknig = 0;

    loadLibrary(books, "library.txt");
    kolvoknig = (int)books.size();

    cout << "Добро пожаловать в систему управления библиотекой!" << endl;
    do {
        cout << "\nМЕНЮ" << endl;
        cout << "1. Добавить книгу" << endl;
        if (kolvoknig != 0) {
            cout << "2. Удалить книгу" << endl;
            cout << "3. Просмотреть все книги" << endl;
            cout << "4. Поиск по названию" << endl;
            cout << "5. Поиск по автору" << endl;
            cout << "6. Поиск по году" << endl;
            cout << "7. Сохранить в файл" << endl;
            cout << "8. Выйти" << endl;
        }
        else cout << "2. Выйти" << endl;

        cout << "Книг в библиотеке: " << kolvoknig << endl;
        cout << "Введите ваш выбор: ";

        while (!(cin >> choice) || (kolvoknig == 0 && choice > 2) || (kolvoknig != 0 && choice > 8)) {
            if (kolvoknig == 0) cout << "Введите значение от 1 до 2";
            else if (kolvoknig != 0) cout << "Введите значение от 1 до 8";
            else cout << "Значение должно быть положительным числом, попробуйте еще раз: "; cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (kolvoknig == 0 && choice == 2) choice = 8;

        switch (choice) {
        case 1: kolvoknig = createBook(books, kolvoknig); break;
        case 2: kolvoknig = Library::deleteBook(books, kolvoknig); break;
        case 3: Library::printbooks(books); break;
        case 4: Library::searchByName(books); break;
        case 5: Library::searchByAuthor(books); break;
        case 6: Library::searchByYear(books); break;
        case 7: saveLibrary(books, "library.txt"); break;
        case 8: saveLibrary(books, "library.txt"); cout << "Выход из программы..." << endl; break;
        }
    } while (choice != 8);
}