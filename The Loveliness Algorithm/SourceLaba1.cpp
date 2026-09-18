#include "MyIncludes.h"
#include "HeaderLaba1.h"

extern bool isAlphaString(const string& str) {
    for (char c : str)
        if (!isalpha(c) && c != ' ' && c != '-')
            return false;
    return true;
}

extern int createBook(vector<Library>& books, int count) {
    bool answer;
    do {
        cout << "\nСоздание книги №" << count + 1 << endl;
        Library book;
        book.input();
        books.push_back(book);
        count++;

        cout << "Добавить еще одну книгу? (yes/no): ";
        string danetka;
        cin.ignore();
        getline(cin, danetka);

        transform(danetka.begin(), danetka.end(), danetka.begin(), ::tolower);
        answer = (danetka == "yes");

    } while (answer);

    return count;
}

extern void loadLibrary(vector<Library>& books, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    Library book;
    string name, author;
    int year;

    while (getline(file, name) && getline(file, author) && (file >> year)) {
        book.setName(name);
        book.setAuthor(author);
        book.setYear(year);
        books.push_back(book);
        file.ignore();
    }

    file.close();
    cout << "Библиотека загружена из файла " << filename << endl;
}

extern void saveLibrary(const vector<Library>& books, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    for (int i = 0; i < books.size(); i++) {
        file << books[i].getName() << endl;
        file << books[i].getAuthor() << endl;
        file << books[i].getYear() << endl;
    }

    file.close();
    cout << "Библиотека сохранена в файл " << filename << endl;
}