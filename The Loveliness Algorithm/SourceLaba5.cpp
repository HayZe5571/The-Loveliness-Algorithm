#include "MyIncludes.h"
#include "HeaderLaba5.h"

Product* findProductByName(const string& name) {
    for (Product* product : products) {
        if (product->getName() == name) {
            return product;
        }
    }
    return nullptr;
}

void displayAllProducts() {
    if (products.empty()) {
        cout << "\nНет данных о товарах!" << endl;
        return;
    }

    cout << "\n=== ВСЕ ТОВАРЫ ===" << endl;

    Product::printTableHeader();

    for (int i = 0; i < (int)products.size(); i++) {
        products[i]->printInfo(i + 1);
    }

    Product::printTableFooter();

    cout << "Всего товаров: " << products.size() << endl;
}

void addProduct() {
    cout << "\n=== ДОБАВЛЕНИЕ ТОВАРОВ ===" << endl;

    int bookCount, accessoriesCount;

    do {
        bookCount = chekInt("Сколько книг добавить", "Количество должно быть неотрицательным", [](int x) { return x >= 0; });
        accessoriesCount = chekInt("Сколько аксессуаров добавить", "Количество должно быть неотрицательным", [](int x) { return x >= 0; });

        if (bookCount + accessoriesCount < 1) {
            cout << "Добавьте хотя бы один товар!" << endl;
        }
    } while (bookCount + accessoriesCount < 1);

    for (int i = 0; i < bookCount; i++) {
        cout << "\n--- Книга " << i + 1 << " ---" << endl;
        Book* product = new Book();
        product->input();
        products.push_back(product);
    }

    for (int i = 0; i < accessoriesCount; i++) {
        cout << "\n--- Аксессуар " << i + 1 << " ---" << endl;
        Accessories* product = new Accessories();
        product->input();
        products.push_back(product);
    }

    int actualBookCount = 0;
    int actualAccessoriesCount = 0;
    for (Product* product : products) {
        if (dynamic_cast<Book*>(product) && !dynamic_cast<BookSet*>(product)) {
            actualBookCount++;
        }
        else if (dynamic_cast<Accessories*>(product) && !dynamic_cast<BookSet*>(product)) {
            actualAccessoriesCount++;
        }
    }

    if (!(actualBookCount >= 1 && actualAccessoriesCount >= 1)) {
                cout << "Недостаточно книг или аксессуаров для создания наборов" << endl;
    }

    int maxPossibleSets = min(actualBookCount, actualAccessoriesCount);
    int setCount = chekInt("Сколько наборов создать из существующих товаров (максимум " + to_string(maxPossibleSets) + ")",
        "Количество должно быть от 0 до " + to_string(maxPossibleSets),
        [maxPossibleSets](int x) { return x >= 0 && x <= maxPossibleSets; });

    for (int i = 0; i < setCount; i++) {
        cout << "\n--- Набор " << i + 1 << " ---" << endl;

        vector<Book*> availableBooks;
        vector<Accessories*> availableAccessories;

        for (Product* product : products) {
            if (Book* book = dynamic_cast<Book*>(product)) {
                if (!dynamic_cast<BookSet*>(product)) {
                    availableBooks.push_back(book);
                }
            }
            else if (Accessories* accessory = dynamic_cast<Accessories*>(product)) {
                if (!dynamic_cast<BookSet*>(product)) {
                    availableAccessories.push_back(accessory);
                }
            }
        }

        cout << "\nДоступные книги:" << endl;
        for (int j = 0; j < availableBooks.size(); j++) {
            cout << j + 1 << ". " << availableBooks[j]->getName() << " (автор: " << availableBooks[j]->getAuthor() << ")" << endl;
        }

        cout << "\nДоступные аксессуары:" << endl;
        for (int j = 0; j < availableAccessories.size(); j++) {
            cout << j + 1 << ". " << availableAccessories[j]->getName() << " (категория: " << availableAccessories[j]->getCategory() << ")" << endl;
        }

        int bookChoice = chekInt("Выберите номер книги", "Неверный номер", [availableBooks](int x) { return x >= 1 && x <= availableBooks.size(); });
        Book* selectedBook = availableBooks[bookChoice - 1];

        int accessoryChoice = chekInt("Выберите номер аксессуара", "Неверный номер", [availableAccessories](int x) { return x >= 1 && x <= availableAccessories.size(); });
        Accessories* selectedAccessory = availableAccessories[accessoryChoice - 1];

        BookSet* product = new BookSet(selectedBook, selectedAccessory);
        products.push_back(product);
        cout << "Набор создан: " << product->getName() << " за " << product->getPrice() << " руб." << endl;
    }

    cout << "\nУспешно добавлено: " << products.size() << " товаров" << endl;
}

void saveToFileProducts(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    file << products.size() << endl;
    for (Product* product : products) {
        product->saveToStream(file);
    }

    file.close();
    cout << "Данные сохранены в файл: " << filename << " (сохранено " << products.size() << " товаров)" << endl;
}

void loadFromFileProducts(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    for (Product* product : products) delete product;
    products.clear();

    int count;
    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        string type;
        getline(file, type);

        Product* product = nullptr;
        if (type == "BOOK") {
            product = new Book();
        }
        else if (type == "ACCESSORIES") {
            product = new Accessories();
        }
        else if (type == "BOOKSET") {
            product = new BookSet();
        }

        if (product != nullptr) {
            product->loadFromStream(file);
            products.push_back(product);
        }
    }

    file.close();
    cout << "Данные загружены из файла: " << filename << " (загружено " << products.size() << " товаров)" << endl;
}

void clearProducts() {
    if (products.empty()) {
        cout << "\nНет данных для очистки!" << endl;
        return;
    }

    bool confirm = danetka("Вы уверены, что хотите удалить все данные о товарах");
    if (!confirm) {
        cout << "Очистка отменена" << endl;
        return;
    }

    for (Product* product : products) delete product;
    products.clear();
    cout << "Все данные о товарах удалены!" << endl;
}