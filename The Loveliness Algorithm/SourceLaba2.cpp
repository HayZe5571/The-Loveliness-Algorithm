#include "MyIncludes.h"
#include "HeaderLaba2.h"

ostream& operator<<(ostream& os, const ArrayFloat& array) {
    os << "Размер массива: " << array.size << endl;
    os << "Элементы массива: ";
    for (int i = 0; i < array.size; i++) {
        os << fixed << setprecision(2) << array.arr[i];
        if (i < array.size - 1) os << ", ";
    }
    return os;
}

istream& operator>>(istream& is, ArrayFloat& array) {
    cout << "Введите размер массива: ";
    int newSize;
    while (!(is >> newSize) || newSize <= 0) {
        cout << "Значение должно быть положительным, попробуйте еще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    delete[] array.arr;
    array.size = newSize;
    array.arr = new float[array.size];

    cout << "Выберите способ заполнения:" << endl;
    cout << "1. Ввести элементы вручную" << endl;
    cout << "2. Заполнить случайными числами" << endl;
    cout << "Ваш выбор: ";

    int fillChoice;
    while (!(is >> fillChoice) || (fillChoice != 1 && fillChoice != 2)) {
        cout << "Выберите 1 или 2: ";
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (fillChoice == 1) {
        cout << "Введите " << array.size << " элементов массива:" << endl;
        for (int i = 0; i < array.size; i++) {
            cout << "Элемент [" << i << "]: ";
            while (!(is >> array.arr[i])) {
                cout << "Значение должно быть числом, попробуйте еще раз: ";
                is.clear();
                is.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else {
        float minValue, maxValue;
        cout << "Введите минимальное значение: ";
        while (!(is >> minValue)) {
            cout << "Значение должно быть числом, попробуйте еще раз: ";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Введите максимальное значение: ";
        while (!(is >> maxValue) || maxValue <= minValue) {
            cout << "Максимальное значение должно быть больше минимального, попробуйте еще раз: ";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        srand(time(0));
        for (int i = 0; i < array.size; i++)
            array.arr[i] = minValue + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxValue - minValue)));
        cout << "Массив заполнен случайными числами от " << minValue << " до " << maxValue << endl;
    }

    return is;
}

void loadFromFile(ArrayFloat& array, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    int fileSize;
    file >> fileSize;

    if (fileSize <= 0) {
        cout << "Ошибка: Неверный размер массива в файле" << endl;
        file.close();
        return;
    }

    float* tempArr = new float[fileSize];

    for (int i = 0; i < fileSize; i++)
        if (!(file >> tempArr[i])) {
            cout << "Ошибка: Не удалось прочитать элемент " << i << " из файла" << endl;
            delete[] tempArr;
            file.close();
            return;
        }

    delete[] array.arr;
    array.size = fileSize;
    array.arr = new float[fileSize];
    copy(tempArr, tempArr + fileSize, array.arr);

    delete[] tempArr;
    file.close();
    cout << "Данные загружены из файла: " << filename << endl;
}

void saveToFile(const ArrayFloat& array, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    file << array.getSize() << endl;
    for (int i = 0; i < array.getSize(); i++)
        file << fixed << setprecision(6) << array.getElement(i) << endl;

    file.close();
    cout << "Данные сохранены в файл: " << filename << endl;
}