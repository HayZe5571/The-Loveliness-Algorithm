#pragma once

class ArrayFloat;

extern void Laba2();

class ArrayFloat {
private:
    float* arr;
    int size;

public:
    ArrayFloat() : arr(nullptr), size(0) {}
    ArrayFloat(int s, float* inputArr) : size(s), arr(new float[s]) {
        copy(inputArr, inputArr + s, arr);
    }
    ArrayFloat(const ArrayFloat& other) : size(other.size), arr(new float[other.size]) {
        copy(other.arr, other.arr + size, arr);
    }
    ~ArrayFloat() { delete[] arr; }

    int getSize() const { return size; }
    float getElement(int index) const { return arr[index]; }

    void display() const {
        if (size == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        cout << "Введите количество столбцов: ";
        int columns;
        while (!(cin >> columns) || columns < 1 || columns > size) {
            cout << "Количество столбцов должно быть не менее 1 и не более размера массива: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Массив:" << endl;
        for (int i = 0; i < size; i++) {
            cout << setw(10) << fixed << setprecision(2) << arr[i];
            if ((i + 1) % columns == 0) cout << endl;
        }

        if (size % columns != 0) cout << endl;
    }
    ArrayFloat& operator=(const ArrayFloat& other) {
        if (this == &other) return *this;

        delete[] arr;
        size = other.size;
        arr = new float[size];
        copy(other.arr, other.arr + size, arr);
    }

    friend ostream& operator<<(ostream& os, const ArrayFloat& array);
    friend istream& operator>>(istream& is, ArrayFloat& array);
    friend void loadFromFile(ArrayFloat& array, const string& filename);
    friend void saveToFile(const ArrayFloat& array, const string& filename);
};