#include "MyIncludes.h"
#include "HeaderLaba8.h"

vector<Exhibit*> exhibits;
vector<ExhibitionHall*> halls;

void addExhibitWithExceptions() {
    cout << "\n=== ДОБАВЛЕНИЕ ЭКСПОНАТА (с обработкой исключений) ===" << endl;

    int typeChoice;
    cout << "Выберите тип (1-Картина, 2-Скульптура): ";
    cin >> typeChoice;
    cin.ignore();

    if (typeChoice != 1 && typeChoice != 2) {
        cout << "Ошибка: Неверный тип экспоната" << endl;
        return;
    }

    Exhibit* newExhibit = nullptr;

    try {
        if (typeChoice == 1) newExhibit = new Painting();
        else newExhibit = new Sculpture();

        newExhibit->input();
        exhibits.push_back(newExhibit);

        if (!halls.empty()) {
            cout << "\nДоступные выставочные залы:" << endl;
            for (size_t i = 0; i < halls.size(); i++) {
                cout << i + 1 << ". " << halls[i]->getHallName()
                    << " (свободно мест: " << halls[i]->getCapacity() - halls[i]->getExhibitCount() << ")" << endl;
            }

            cout << "Добавить экспонат в выставочный зал? (1-Да, 0-Нет): ";
            int addToHall;
            cin >> addToHall;
            cin.ignore();

            if (addToHall == 1) {
                cout << "Выберите номер зала: ";
                int hallChoice;
                cin >> hallChoice;
                cin.ignore();

                if (hallChoice < 1 || hallChoice > halls.size()) {
                    cout << "Ошибка: Неверный номер зала" << endl;
                    return;
                }

                halls[hallChoice - 1]->addExhibit(newExhibit);
                cout << "Экспонат добавлен в зал '" << halls[hallChoice - 1]->getHallName() << "'" << endl;
            }
        }

        cout << "\nЭкспонат успешно добавлен!" << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        if (newExhibit) delete newExhibit;
        return;
    }
    catch (...) {
        cout << "Неизвестная ошибка" << endl;
        if (newExhibit) delete newExhibit;
        return;
    }
}

void addExhibitionHall() {
    cout << "\n=== ДОБАВЛЕНИЕ ВЫСТАВОЧНОГО ЗАЛА ===" << endl;

    ExhibitionHall* newHall = new ExhibitionHall();

    try {
        newHall->input();
        halls.push_back(newHall);
        cout << "\nВыставочный зал успешно создан!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        delete newHall;
        return;
    }
    catch (...) {
        cout << "Неизвестная ошибка" << endl;
        delete newHall;
        return;
    }
}

void displayAllExhibits() {
    if (exhibits.empty() && halls.empty()) {
        cout << "\nНет данных для отображения!" << endl;
        return;
    }

    if (!exhibits.empty()) {
        cout << "\n=== ВСЕ ЭКСПОНАТЫ ===" << endl;
        Exhibit::printTableHeader();
        for (size_t i = 0; i < exhibits.size(); i++) exhibits[i]->printInfo(i + 1);
        Exhibit::printTableFooter();
        cout << "Всего экспонатов: " << exhibits.size() << endl;

        double totalValue = 0;
        for (Exhibit* exhibit : exhibits) totalValue += exhibit->getPrice();
        cout << "Общая стоимость коллекции: " << totalValue << " тыс. руб." << endl;
    }

    if (!halls.empty()) {
        cout << "\n=== ВЫСТАВОЧНЫЕ ЗАЛЫ ===" << endl;
        for (size_t i = 0; i < halls.size(); i++) {
            cout << "\nЗал " << i + 1 << ":" << endl;
            halls[i]->printInfo();
            if (halls[i]->getExhibitCount() > 0) halls[i]->printExhibitsTable();
        }
    }
}

void saveToFile(const string& filename) {
    try {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл для записи");

        file << exhibits.size() << endl;
        for (Exhibit* exhibit : exhibits) {
            if (Painting* painting = dynamic_cast<Painting*>(exhibit)) painting->saveToStream(file);
            else if (Sculpture* sculpture = dynamic_cast<Sculpture*>(exhibit)) sculpture->saveToStream(file);
        }

        file << halls.size() << endl;
        for (ExhibitionHall* hall : halls) hall->saveToStream(file);

        file.close();
        cout << "Данные сохранены в файл: " << filename << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при сохранении: " << e.what() << endl;
    }
}

void loadFromFile(const string& filename) {
    try {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл для чтения");

        clearAllData8();

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

        int hallCount;
        file >> hallCount;
        file.ignore();

        for (int i = 0; i < hallCount; i++) {
            ExhibitionHall* hall = new ExhibitionHall();
            hall->loadFromStream(file);
            halls.push_back(hall);
        }

        file.close();
        cout << "Данные загружены из файла: " << filename << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при загрузке: " << e.what() << endl;
        clearAllData8();
    }
}

void clearAllData8() {
    if (exhibits.empty() && halls.empty()) {
        cout << "\nНет данных для очистки!" << endl;
        return;
    }

    cout << "Вы уверены, что хотите удалить все данные выставки? (1-Да, 0-Нет): ";
    int confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 1) {
        cout << "Очистка отменена" << endl;
        return;
    }

    for (Exhibit* exhibit : exhibits) delete exhibit;
    exhibits.clear();

    for (ExhibitionHall* hall : halls) delete hall;
    halls.clear();

    cout << "Все данные выставки удалены!" << endl;
}