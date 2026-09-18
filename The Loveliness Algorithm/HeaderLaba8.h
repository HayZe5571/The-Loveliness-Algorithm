#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <exception>
using namespace std;

extern vector<class Exhibit*> exhibits;
extern vector<class ExhibitionHall*> halls;

extern void Laba8();
extern void addExhibitWithExceptions();
extern void addExhibitionHall();
extern void displayAllExhibits();
extern void saveToFile(const string& filename);
extern void loadFromFile(const string& filename);
extern void clearAllData8();

class GalleryException : public exception {
private:
    string message;
public:
    GalleryException(const string& msg) : message("Галерея: " + msg) {
        cout << "Конструктор GalleryException(\"" << msg << "\") - создание исключения" << endl;
    }

    ~GalleryException() noexcept {
        cout << "Деструктор ~GalleryException()" << endl;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Exhibit {
protected:
    string title;
    string artist;
    int year;
    double price;
    bool isValid;

public:
    Exhibit() : title(""), artist(""), year(0), price(0), isValid(false) {
        cout << "Конструктор Exhibit() - создание пустого экспоната" << endl;
    }
    Exhibit(const string& title, const string& artist, int year, double price)
        : title(title), artist(artist), year(year), price(price), isValid(true) {
        cout << "Конструктор Exhibit(\"" << title << "\", \"" << artist
            << "\", " << year << ", " << price << ") - создание экспоната" << endl;
        if (title.empty()) throw invalid_argument("Название экспоната не может быть пустым");
        if (price <= 0) throw GalleryException("Цена должна быть положительной");
        if (year < 1000 || year > 2100) throw out_of_range("Год должен быть между 1000 и 2100");
    }
    Exhibit(const Exhibit& other)
        : title(other.title), artist(other.artist), year(other.year),
        price(other.price), isValid(other.isValid) {
    }
    virtual ~Exhibit() {
        cout << "Деструктор ~Exhibit() - удаление экспоната \"" << title << "\"" << endl;
    }

    string getTitle() const { return title; }
    string getArtist() const { return artist; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    bool getIsValid() const { return isValid; }

    void setTitle(const string& title) {
        if (title.empty()) throw invalid_argument("Название не может быть пустым");
        this->title = title;
    }
    void setArtist(const string& artist) { this->artist = artist; }
    void setYear(int year) {
        if (year < 1000 || year > 2100) throw out_of_range("Некорректный год");
        this->year = year;
    }
    void setPrice(double price) {
        if (price <= 0) throw GalleryException("Цена должна быть положительной");
        this->price = price;
    }

    virtual string getType() const = 0;

    virtual void input() {
        try {
            cout << "Введите название: ";
            getline(cin, title);
            if (title.empty()) throw invalid_argument("Название не может быть пустым");

            cout << "Введите автора: ";
            getline(cin, artist);
            if (artist.empty()) throw invalid_argument("Автор не может быть пустым");

            cout << "Введите год создания: ";
            cin >> year;
            cin.ignore();
            if (year < 1000 || year > 2100) throw out_of_range("Год должен быть между 1000 и 2100");

            cout << "Введите цену (в тыс. руб.): ";
            cin >> price;
            cin.ignore();
            if (price <= 0) throw GalleryException("Цена должна быть положительной");

            isValid = true;
        }
        catch (const exception& e) {
            isValid = false;
            throw;
        }
    }

    virtual void printInfo(int index) const {
        cout << "| " << setw(3) << index << " | "
            << setw(25) << (title.length() > 24 ? title.substr(0, 22) + ".." : title) << " | "
            << setw(20) << (artist.length() > 19 ? artist.substr(0, 17) + ".." : artist) << " | "
            << setw(8) << year << " | "
            << setw(12) << price << " | "
            << setw(30) << getType() << " |" << endl;
    }

    virtual void printDetailedInfo() const {
        cout << "Название: " << title << endl;
        cout << "Автор: " << artist << endl;
        cout << "Год: " << year << endl;
        cout << "Цена: " << price << " тыс. руб." << endl;
        cout << "Тип: " << getType() << endl;
    }

    virtual void saveToStream(ofstream& file) const {
        file << title << endl;
        file << artist << endl;
        file << year << endl;
        file << price << endl;
        file << isValid << endl;
    }

    virtual void loadFromStream(ifstream& file) {
        getline(file, title);
        getline(file, artist);
        file >> year;
        file >> price;
        file >> isValid;
        file.ignore();
    }

    static void printTableHeader() {
        cout << "+-----+---------------------------+----------------------+----------+--------------+--------------------------------+" << endl;
        cout << "|  №  |         Название          |       Автор          |   Год    |   Цена (тыс.)|              Тип               |" << endl;
        cout << "+-----+---------------------------+----------------------+----------+--------------+--------------------------------+" << endl;
    }

    static void printTableFooter() {
        cout << "+-----+---------------------------+----------------------+----------+--------------+--------------------------------+" << endl;
    }
};

class Painting : public Exhibit {
private:
    string style;
    string medium;
    double width;
    double height;

public:
    Painting() : Exhibit(), style(""), medium(""), width(0), height(0) {
        cout << "Конструктор Painting() - создание пустой картины" << endl;
    }
    Painting(const string& title, const string& artist, int year, double price,
        const string& style, const string& medium, double width, double height)
        : Exhibit(title, artist, year, price), style(style), medium(medium),
        width(width), height(height) {
        cout << "Конструктор Painting(\"" << title << "\", ...) - создание картины \""
            << title << "\" размера " << width << "x" << height << " см" << endl;
        if (width <= 0 || height <= 0) throw invalid_argument("Размеры картины должны быть положительными");
    }
    ~Painting() override {
        cout << "Деструктор ~Painting() - удаление картины \"" << getTitle() << "\"" << endl;
    }

    string getStyle() const { return style; }
    string getMedium() const { return medium; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getArea() const { return width * height; }

    void setStyle(const string& style) { this->style = style; }
    void setMedium(const string& medium) { this->medium = medium; }
    void setWidth(double width) {
        if (width <= 0) throw invalid_argument("Ширина должна быть > 0");
        this->width = width;
    }
    void setHeight(double height) {
        if (height <= 0) throw invalid_argument("Высота должна быть > 0");
        this->height = height;
    }

    string getType() const override { return "Картина"; }

    void input() override {
        try {
            Exhibit::input();
            cout << "Введите стиль: ";
            getline(cin, style);
            if (style.empty()) throw invalid_argument("Стиль не может быть пустым");

            cout << "Введите технику (масло, акварель и т.д.): ";
            getline(cin, medium);
            if (medium.empty()) throw invalid_argument("Техника не может быть пустой");

            cout << "Введите ширину (см): ";
            cin >> width;
            cin.ignore();
            if (width <= 0) throw invalid_argument("Ширина должна быть > 0");

            cout << "Введите высоту (см): ";
            cin >> height;
            cin.ignore();
            if (height <= 0) throw invalid_argument("Высота должна быть > 0");
        }
        catch (const exception& e) {
            throw;
        }
    }

    void printInfo(int index) const override {
        cout << "| " << setw(3) << index << " | "
            << setw(25) << (getTitle().length() > 24 ? getTitle().substr(0, 22) + ".." : getTitle()) << " | "
            << setw(20) << (getArtist().length() > 19 ? getArtist().substr(0, 17) + ".." : getArtist()) << " | "
            << setw(8) << getYear() << " | "
            << setw(12) << getPrice() << " | "
            << setw(30) << "Картина (" + style + ")" << " |" << endl;
    }

    void printDetailedInfo() const override {
        Exhibit::printDetailedInfo();
        cout << "Стиль: " << style << endl;
        cout << "Техника: " << medium << endl;
        cout << "Размеры: " << width << "x" << height << " см" << endl;
        cout << "Площадь: " << getArea() << " кв.см" << endl;
    }

    void saveToStream(ofstream& file) const override {
        file << "PAINTING" << endl;
        Exhibit::saveToStream(file);
        file << style << endl;
        file << medium << endl;
        file << width << endl;
        file << height << endl;
    }

    void loadFromStream(ifstream& file) override {
        Exhibit::loadFromStream(file);
        getline(file, style);
        getline(file, medium);
        file >> width;
        file >> height;
        file.ignore();
    }
};

class Sculpture : public Exhibit {
private:
    string material;
    double weight;
    bool isInteractive;

public:
    Sculpture() : Exhibit(), material(""), weight(0), isInteractive(false) {
        cout << "Конструктор Sculpture() - создание пустой скульптуры" << endl;
    }

    Sculpture(const string& title, const string& artist, int year, double price,
        const string& material, double weight, bool isInteractive)
        : Exhibit(title, artist, year, price), material(material),
        weight(weight), isInteractive(isInteractive) {
        cout << "Конструктор Sculpture(\"" << title << "\", ...) - создание скульптуры \""
            << title << "\" из " << material << " весом " << weight << " кг" << endl;
        if (weight <= 0) throw invalid_argument("Вес должен быть положительным");
    }

    ~Sculpture() override {
        cout << "Деструктор ~Sculpture() - удаление скульптуры \"" << getTitle() << "\"" << endl;
    }

    string getMaterial() const { return material; }
    double getWeight() const { return weight; }
    bool getIsInteractive() const { return isInteractive; }

    void setMaterial(const string& material) { this->material = material; }
    void setWeight(double weight) {
        if (weight <= 0) throw invalid_argument("Вес должен быть > 0");
        this->weight = weight;
    }
    void setIsInteractive(bool isInteractive) { this->isInteractive = isInteractive; }

    string getType() const override { return "Скульптура"; }

    void input() override {
        try {
            Exhibit::input();
            cout << "Введите материал: ";
            getline(cin, material);
            if (material.empty()) throw invalid_argument("Материал не может быть пустым");

            cout << "Введите вес (кг): ";
            cin >> weight;
            cin.ignore();
            if (weight <= 0) throw invalid_argument("Вес должен быть > 0");

            cout << "Это интерактивная скульптура? (1-Да, 0-Нет): ";
            int choice;
            cin >> choice;
            cin.ignore();
            if (choice != 0 && choice != 1) throw invalid_argument("Введите 1 или 0");
            isInteractive = (choice == 1);
        }
        catch (const exception& e) {
            throw;
        }
    }

    void printInfo(int index) const override {
        cout << "| " << setw(3) << index << " | "
            << setw(25) << (getTitle().length() > 24 ? getTitle().substr(0, 22) + ".." : getTitle()) << " | "
            << setw(20) << (getArtist().length() > 19 ? getArtist().substr(0, 17) + ".." : getArtist()) << " | "
            << setw(8) << getYear() << " | "
            << setw(12) << getPrice() << " | "
            << setw(30) << "Скульптура (" + material + ")" << " |" << endl;
    }

    void printDetailedInfo() const override {
        Exhibit::printDetailedInfo();
        cout << "Материал: " << material << endl;
        cout << "Вес: " << weight << " кг" << endl;
        cout << "Тип: " << (isInteractive ? "Интерактивная" : "Статичная") << endl;
    }

    void saveToStream(ofstream& file) const override {
        file << "SCULPTURE" << endl;
        Exhibit::saveToStream(file);
        file << material << endl;
        file << weight << endl;
        file << isInteractive << endl;
    }

    void loadFromStream(ifstream& file) override {
        Exhibit::loadFromStream(file);
        getline(file, material);
        file >> weight;
        file >> isInteractive;
        file.ignore();
    }
};

class ExhibitionHall {
private:
    string hallName;
    int capacity;
    double area;
    vector<Exhibit*> exhibits;
    int nextExhibitId;

public:
    ExhibitionHall() : hallName(""), capacity(0), area(0), nextExhibitId(1) {
        cout << "Конструктор ExhibitionHall() - создание пустого выставочного зала" << endl;
    }

    ExhibitionHall(const string& hallName, int capacity, double area)
        : hallName(hallName), capacity(capacity), area(area), nextExhibitId(1) {
        cout << "Конструктор ExhibitionHall(\"" << hallName << "\", "
            << capacity << ", " << area << ") - создание выставочного зала" << endl;
        if (hallName.empty()) throw invalid_argument("Название зала не может быть пустым");
        if (capacity <= 0) throw invalid_argument("Вместимость должна быть > 0");
        if (area <= 0) throw invalid_argument("Площадь должна быть > 0");

        try {
            cout << "  Попытка создать большой массив для демонстрации bad_alloc..." << endl;
            Painting* largeArray = new Painting[1000000000];
            delete[] largeArray;
        }
        catch (const bad_alloc& e) {
            cout << "  ! Поймано исключение bad_alloc в конструкторе ExhibitionHall!" << endl;
            throw GalleryException("Недостаточно памяти для создания зала");
        }
    }

    ~ExhibitionHall() {
        cout << "Деструктор ~ExhibitionHall() - удаление зала \"" << hallName << "\" с "
            << exhibits.size() << " экспонатами" << endl;
        clearExhibits();
    }

    string getHallName() const { return hallName; }
    int getCapacity() const { return capacity; }
    double getArea() const { return area; }
    vector<Exhibit*> getExhibits() const { return exhibits; }
    int getExhibitCount() const { return exhibits.size(); }

    void setHallName(const string& hallName) {
        if (hallName.empty()) throw invalid_argument("Название зала не может быть пустым");
        this->hallName = hallName;
    }
    void setCapacity(int capacity) {
        if (capacity <= 0) throw invalid_argument("Вместимость должна быть > 0");
        this->capacity = capacity;
    }
    void setArea(double area) {
        if (area <= 0) throw invalid_argument("Площадь должна быть > 0");
        this->area = area;
    }

    void addExhibit(Exhibit* exhibit) {
        if (exhibits.size() >= capacity) throw GalleryException("Превышена вместимость зала");
        exhibits.push_back(exhibit);
    }

    void removeExhibit(int index) {
        if (index < 0 || index >= exhibits.size()) throw out_of_range("Неверный индекс экспоната");
        delete exhibits[index];
        exhibits.erase(exhibits.begin() + index);
    }

    void clearExhibits() {
        for (Exhibit* exhibit : exhibits) delete exhibit;
        exhibits.clear();
    }

    double calculateTotalValue() const {
        double total = 0;
        for (Exhibit* exhibit : exhibits) total += exhibit->getPrice();
        return total;
    }

    void input() {
        try {
            cout << "Введите название зала: ";
            getline(cin, hallName);
            if (hallName.empty()) throw invalid_argument("Название зала не может быть пустым");

            cout << "Введите вместимость (количество экспонатов): ";
            cin >> capacity;
            cin.ignore();
            if (capacity <= 0) throw invalid_argument("Вместимость должна быть > 0");

            cout << "Введите площадь зала (кв.м): ";
            cin >> area;
            cin.ignore();
            if (area <= 0) throw invalid_argument("Площадь должна быть > 0");
        }
        catch (const exception& e) {
            throw;
        }
    }

    void printInfo() const {
        cout << "Зал: " << hallName << endl;
        cout << "Вместимость: " << capacity << " экспонатов" << endl;
        cout << "Площадь: " << area << " кв.м" << endl;
        cout << "Количество экспонатов: " << exhibits.size() << endl;
        cout << "Общая стоимость экспонатов: " << calculateTotalValue() << " тыс. руб." << endl;
    }

    void printExhibitsTable() const {
        if (exhibits.empty()) {
            cout << "В зале нет экспонатов" << endl;
            return;
        }
        cout << "\nЭкспонаты в зале '" << hallName << "':" << endl;
        Exhibit::printTableHeader();
        for (int i = 0; i < exhibits.size(); i++) exhibits[i]->printInfo(i + 1);
        Exhibit::printTableFooter();
    }

    void saveToStream(ofstream& file) const {
        file << hallName << endl;
        file << capacity << endl;
        file << area << endl;
        file << exhibits.size() << endl;

        for (Exhibit* exhibit : exhibits) {
            if (Painting* painting = dynamic_cast<Painting*>(exhibit)) painting->saveToStream(file);
            else if (Sculpture* sculpture = dynamic_cast<Sculpture*>(exhibit)) sculpture->saveToStream(file);
        }
    }

    void loadFromStream(ifstream& file) {
        clearExhibits();
        getline(file, hallName);
        file >> capacity;
        file >> area;

        int exhibitCount;
        file >> exhibitCount;
        file.ignore();

        for (int i = 0; i < exhibitCount; i++) {
            string type;
            getline(file, type);
            Exhibit* exhibit = nullptr;
            if (type == "PAINTING") exhibit = new Painting();
            else if (type == "SCULPTURE") exhibit = new Sculpture();
            if (exhibit) {
                exhibit->loadFromStream(file);
                exhibits.push_back(exhibit);
            }
        }
    }
};