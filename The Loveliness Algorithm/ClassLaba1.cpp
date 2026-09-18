#include "MyIncludes.h"
#include "HeaderLaba1.h"

Library::Library() : name("Отцы и дети"), author("Тургенев"), year(2020) { }
Library::Library(const string& n, const string& a, int y) {
    setName(n);
    setAuthor(a);
    setYear(y);
}
Library::Library(const Library& other) {
    name = other.name;
    author = other.author;
    year = other.year;
}
Library::~Library() { }

void Library::setName(const string& n) { if (!n.empty()) name = n; }
void Library::setAuthor(const string& a) { if (!a.empty() && isAlphaString(a)) author = a; }
void Library::setYear(int y) { if (y > 0 && y <= 2025) year = y; }

string Library::getName() const { return name; }
string Library::getAuthor() const { return author; }
int Library::getYear() const { return year; }

void Library::input() {
    cout << "Введите данные книги" << endl;
    cin.ignore();

    cout << "Название: ";
    getline(cin, name);
    while (name.empty()) {
        cout << "Название не может быть пустым! Введите снова: ";
        getline(cin, name);
    }

    cout << "Автор: ";
    getline(cin, author);
    while (author.empty() || !isAlphaString(author)) {
        cout << "Автор должен содержать только буквы, пробелы и дефисы! Введите снова: ";
        getline(cin, author);
    }

    cout << "Год издания: ";
    while (!(cin >> year) || year <= 0 || year > 2025) {
        if (year < 0) cout << "МЫ НЕ ХРАНИМ ТАКИЕ ДРЕВНИЕ КНИГИ! Введите снова: " << endl;
        else if (year > 2025)cout << "МЫ НЕ ХРАНИМ КНИГИ ИЗ БУДУЩЕГО! Введите снова: " << endl;
        else cout << "Значение должно быть числом, попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int Library::deleteBook(vector<Library>& books, int count) {
    printbooks(books);
    cout << "Введите номер книги для удаления (1-" << books.size() << "): ";
    int index;
    while (!(cin >> index) || index < 1 || index > books.size()) {
        cout << "Значение должно быть одним из предложенных, попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    books.erase(books.begin() + index - 1);
    cout << "Книга №" << index << " удалена успешно!" << endl;
    return count - 1;
}

void Library::output(int number) const {
    cout << "Книга №" << number << endl;
    cout << "Название:    " << name << endl;
    cout << "Автор:       " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << string(30, '-') << endl;
}

void Library::printbooks(const vector<Library>& books) {
    cout << "\nСписок всех книг в библиотеке:" << endl;
    cout << string(30, '-') << endl;

    for (int i = 0; i < books.size(); i++) books[i].output(i);
}

void Library::searchByName(const vector<Library>& books) {
    string name;
    cout << "Введите название для поиска: ";
    cin.ignore();
    getline(cin, name);
    while (name.empty()) {
        cout << "Название не может быть пустым! Введите снова: ";
        getline(cin, name);
    }

    bool found = false;
    cout << "\nРезультаты поиска по названию '" << name << "':" << endl;
    cout << string(50, '-') << endl;

    for (int i = 0; i < books.size(); i++) {
        if (books[i].getName() == name) {
            books[i].output(i);
            found = true;
        }
    }

    if (!found) cout << "Книги с названием '" << name << "' не найдены" << endl;
}

void Library::searchByAuthor(const vector<Library>& books) {
    string author;
    cout << "Введите автора для поиска: ";
    cin.ignore();
    getline(cin, author);
    while (author.empty() || !isAlphaString(author)) {
        cout << "Автор должен содержать только буквы, пробелы и дефисы! Введите снова: ";
        getline(cin, author);
    }

    bool found = false;
    cout << "\nРезультаты поиска по автору '" << author << "':" << endl;
    cout << string(50, '-') << endl;

    for (int i = 0; i < books.size(); i++) {
        if (books[i].getAuthor() == author) {
            books[i].output(i);
            found = true;
        }
    }

    if (!found) cout << "Книги автора '" << author << "' не найдены" << endl;
}

void Library::searchByYear(const vector<Library>& books) {
    cout << "Введите год для поиска: ";
    int year;
    while (!(cin >> year) || year <= 0 || year > 2025) {
        if (year < 0) cout << "МЫ НЕ ХРАНИМ ТАКИЕ ДРЕВНИЕ КНИГИ! Введите снова: " << endl;
        else if (year > 2025)cout << "МЫ НЕ ХРАНИМ КНИГИ ИЗ БУДУЩЕГО! Введите снова: " << endl;
        else cout << "Значение должно быть числом, попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool found = false;
    cout << "\nРезультаты поиска по году " << year << ":" << endl;
    cout << string(50, '-') << endl;

    for (int i = 0; i < books.size(); i++) {
        if (books[i].getYear() == year) {
            books[i].output(i);
            found = true;
        }
    }

    if (!found) cout << "Книги " << year << " года не найдены" << endl;
}