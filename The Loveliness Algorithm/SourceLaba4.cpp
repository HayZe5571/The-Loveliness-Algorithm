#include "MyIncludes.h"
#include "HeaderLaba4.h"

vector<FlatFigure*> shapes;

void addShape() {
    cout << "\n=== ДОБАВЛЕНИЕ ФИГУР ===" << endl;

    int circleCount, rectCount;

    do {
        circleCount = chekInt("Сколько кругов добавить", "Количество должно быть неотрицательным", [](int x) { return x >= 0; });
        rectCount = chekInt("Сколько прямоугольников добавить", "Количество должно быть неотрицательным", [](int x) { return x >= 0; });
        if (circleCount + rectCount < 1) cout << "Добавьте хотя бы одну фигуру!" << endl;
    } while (circleCount + rectCount < 1);

    for (int i = 0; i < circleCount; i++) {
        cout << "\n--- Круг " << i + 1 << " ---" << endl;
        Circle* circle = new Circle();
        circle->input();
        shapes.push_back(circle);
    }

    for (int i = 0; i < rectCount; i++) {
        cout << "\n--- Прямоугольник " << i + 1 << " ---" << endl;
        Rectangleу* rect = new Rectangleу();
        rect->input();
        shapes.push_back(rect);
    }

    cout << "\nУспешно добавлено: " << shapes.size() << " фигур" << endl;
}
void displayAllShapes() {
    if (shapes.empty()) {
        cout << "\nНет данных о фигурах!" << endl;
        return;
    }

    cout << "\n=== ВСЕ ФИГУРЫ ===" << endl;
    FlatFigure::printTableHeader();
    for (int i = 0; i < (int)shapes.size(); i++) shapes[i]->printInfo(i);
    FlatFigure::printTableFooter();
    cout << "Всего фигур: " << shapes.size() << endl;
}

void saveToFileShapes(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    file << shapes.size() << endl;
    for (FlatFigure* shape : shapes) shape->saveToFile(file);

    file.close();
    cout << "Данные сохранены в файл: " << filename << " (сохранено " << shapes.size() << " фигур)" << endl;
}
void loadFromFileShapes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    for (FlatFigure* shape : shapes) delete shape;
    shapes.clear();

    int count;
    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        string type;
        getline(file, type);

        if (type == "CIRCLE") {
            Circle* circle = new Circle();
            circle->loadFromFile(file);
            shapes.push_back(circle);
        }
        else if (type == "RECTANGLE") {
            Rectangleу* rect = new Rectangleу();
            rect->loadFromFile(file);
            shapes.push_back(rect);
        }
    }

    file.close();
    cout << "Данные загружены из файла: " << filename << " (загружено " << shapes.size() << " фигур)" << endl;
}

void clearShapes() {
    if (shapes.empty()) {
        cout << "\nНет данных для очистки!" << endl;
        return;
    }

    bool confirm = danetka("Вы уверены, что хотите удалить все данные о фигурах");
    if (!confirm) {
        cout << "Очистка отменена" << endl;
        return;
    }

    for (FlatFigure* shape : shapes) delete shape;
    shapes.clear();
    cout << "Все данные о фигурах удалены!" << endl;
}