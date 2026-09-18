#pragma once

class Product;
class Book;
class Accessories;
class BookSet;

extern vector<Product*> products;
extern void Laba5();

extern void addProduct();
extern void displayAllProducts();
extern void saveToFileProducts(const string& filename);
extern void loadFromFileProducts(const string& filename);
extern void clearProducts();
extern Product* findProductByName(const string& name);

class Product {
protected:
    int id = 0;
    string name;
    double price = 0.0;

public:
    virtual ~Product() = default;

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getId() const { return id; }

    void setName(const string& name) { this->name = name; }
    void setPrice(double price) { this->price = price; }
    void setId(int id) { this->id = id; }

    virtual string getType() const = 0;
    virtual void input() = 0;
    virtual void printInfo(int index) const = 0;

    virtual void saveToStream(ofstream& file) const = 0;
    virtual void loadFromStream(ifstream& file) = 0;

    static void printTableHeader() {
        cout << "+-----+---------------------------+------------+------------+------------------+------------------+------------------+" << endl;
        cout << "|  №  |           Название        |     ID     |   Цена     |       Тип        |     Автор        |    Категория     |" << endl;
        cout << "+-----+---------------------------+------------+------------+------------------+------------------+------------------+" << endl;
    }

    static void printTableFooter() {
        cout << "+-----+---------------------------+------------+------------+------------------+------------------+------------------+" << endl;
    }
};

class Book : virtual public Product {
protected:
    string author;
    string genre;

public:
    Book() = default;
    Book(int id, string name, double price, string author, string genre)
        : author(author), genre(genre) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
    Book(const Book& other) = default;
    virtual ~Book() = default;

    string getAuthor() const { return author; }
    string getGenre() const { return genre; }

    void setAuthor(const string& author) { this->author = author; }
    void setGenre(const string& genre) { this->genre = genre; }

    string getType() const override { return "Книга"; }

    void input() override {
        cout << "Введите название книги: ";
        getline(cin, name);
        cout << "Введите автора книги: ";
        getline(cin, author);
        cout << "Введите жанр книги: ";
        getline(cin, genre);
        price = chekDouble("Введите цену книги", "Цена должна быть положительной", [](double x) { return x > 0; });
        id = rand() % 10000;
    }

    void printInfo(int index) const override {
        cout << "| " << setw(3) << index << " | "
            << setw(25) << name.substr(0, 24) << " | "
            << setw(10) << id << " | "
            << setw(10) << price << " | "
            << setw(16) << getType() << " | "
            << setw(16) << author.substr(0, 15) << " | "
            << setw(16) << "" << " |" << endl;
    }

    void saveToStream(ofstream& file) const override {
        file << "BOOK" << endl;
        file << id << endl << name << endl << price << endl;
        file << author << endl << genre << endl;
    }

    void loadFromStream(ifstream& file) override {
        file >> id;
        file.ignore();
        getline(file, name);
        file >> price;
        file.ignore();
        getline(file, author);
        getline(file, genre);
    }
};

class Accessories : virtual public Product {
protected:
    string category;

public:
    Accessories() = default;
    Accessories(int id, string name, double price, string category)
        : category(category) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
    Accessories(const Accessories& other) = default;
    virtual ~Accessories() = default;

    string getCategory() const { return category; }

    void setCategory(const string& category) { this->category = category; }

    string getType() const override { return "Аксессуар"; }

    void input() override {
        cout << "Введите название аксессуара: ";
        getline(cin, name);
        cout << "Введите категорию аксессуара: ";
        getline(cin, category);
        price = chekDouble("Введите цену аксессуара", "Цена должна быть положительной", [](double x) { return x > 0; });
        id = rand() % 10000;
    }

    void printInfo(int index) const override {
        cout << "| " << setw(3) << index << " | "
            << setw(25) << name.substr(0, 24) << " | "
            << setw(10) << id << " | "
            << setw(10) << price << " | "
            << setw(16) << getType() << " | "
            << setw(16) << "" << " | "
            << setw(16) << category.substr(0, 15) << " |" << endl;
    }

    void saveToStream(ofstream& file) const override {
        file << "ACCESSORIES" << endl;
        file << id << endl << name << endl << price << endl;
        file << category << endl;
    }

    void loadFromStream(ifstream& file) override {
        file >> id;
        file.ignore();
        getline(file, name);
        file >> price;
        file.ignore();
        getline(file, category);
    }
};

class BookSet : public Book, public Accessories {
public:
    BookSet() = default;
    BookSet(Book* book, Accessories* accessory) {
        this->id = rand() % 10000;
        this->name = book->getName() + " + " + accessory->getName();
        this->price = book->getPrice() + accessory->getPrice();
        this->author = book->getAuthor();
        this->genre = book->getGenre();
        this->category = accessory->getCategory();
    }
    BookSet(const BookSet& other) = default;
    virtual ~BookSet() = default;

    string getType() const override { return "Набор"; }

    void input() override {
        cout << "Создание набора из существующих товаров..." << endl;
    }

    void printInfo(int index) const override {
        cout << "| " << setw(3) << index << " | "
            << setw(25) << name.substr(0, 24) << " | "
            << setw(10) << id << " | "
            << setw(10) << price << " | "
            << setw(16) << getType() << " | "
            << setw(16) << author.substr(0, 15) << " | "
            << setw(16) << category.substr(0, 15) << " |" << endl;
    }

    void saveToStream(ofstream& file) const override {
        file << "BOOKSET" << endl;
        file << id << endl << name << endl << price << endl;
        file << author << endl << genre << endl;
        file << category << endl;
    }

    void loadFromStream(ifstream& file) override {
        file >> id;
        file.ignore();
        getline(file, name);
        file >> price;
        file.ignore();
        getline(file, author);
        getline(file, genre);
        getline(file, category);
    }
};