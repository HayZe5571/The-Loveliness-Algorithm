#include "MyIncludes.h"
#include "HeaderLaba2.h"

ArrayFloat::ArrayFloat() : arr(nullptr), size(0) {}
ArrayFloat::ArrayFloat(int s, float* inputArr) : size(s), arr(new float[s]) {
    copy(inputArr, inputArr + s, arr);
}
ArrayFloat::ArrayFloat(const ArrayFloat& other) : size(other.size), arr(new float[other.size]) {
    copy(other.arr, other.arr + size, arr);
}
ArrayFloat::~ArrayFloat() { delete[] arr; }

int ArrayFloat::getSize() const { return size; }
float ArrayFloat::getElement(int index) const { return arr[index]; }

void ArrayFloat::display() const {
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

ArrayFloat& ArrayFloat::operator=(const ArrayFloat& other) {
    if (this != &other) {
        delete[] arr;
        size = other.size;
        arr = new float[size];
        copy(other.arr, other.arr + size, arr);
    }
    return *this;
}