#pragma once

#define NOMINMAX

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <concepts>
#include <functional>
#include <memory>
#include <stdexcept> 
#include <exception> 
#include <random>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <locale>
#include <windows.h>

using namespace std;

inline bool danetka(const string& prompt) {
    cout << prompt + ": ";

    do {
        string answer;
        getline(cin, answer);
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer == "да" || answer == "д") return true;
        else if (answer == "нет" || answer == "н") return false;
        else cout << "Пожалуйста, введите 'да' или 'нет': ";
    } while (true);
}

inline static string toLower(const string& str) {
    string result = str;
    for (char& c : result)  c = tolower(c);

    return result;
}

template<typename T>
T chek(const string& prompt, const string& error, function<T(T)> customCheck = [](T x) { return true; }) {
    cout << prompt + ": ";

    T n;
    while (!(cin >> n) || !customCheck(n)) {
        cerr << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}

/*                     СТРУКТУРА ЗАПИСИ ПРОВЕРКИ
*
* тип_результата имя_переменной = chekТип("подсказка", "сообщение_ошибки",
*   [](тип_параметра x) { return условие_для_х;});
*/

inline int chekInt(const string& prompt, const string& error, function<bool(int)> customCheck = [](int x) { return true; }) {
    cout << prompt + ": ";

    int n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}
inline unsigned int chekUnsignedInt(const string& prompt, const string& error, function<bool(unsigned int)> customCheck = [](unsigned int x) { return true; }) {
    cout << prompt + ": ";

    unsigned int n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}

inline long chekLong(const string& prompt, const string& error, function<bool(long)> customCheck = [](long x) { return true; }) {
    cout << prompt + ": ";

    long n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}
inline unsigned long chekUnsignedLong(const string& prompt, const string& error, function<bool(unsigned long)> customCheck = [](unsigned long x) { return true; }) {
    cout << prompt + ": ";

    unsigned long n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}

inline float chekFloat(const string& prompt, const string& error, function<bool(float)> customCheck = [](float x) { return true; }) {
    cout << prompt + ": ";

    float n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}
inline double chekDouble(const string& prompt, const string& error, function<bool(double)> customCheck = [](double x) { return true; }) {
    cout << prompt + ": ";

    double n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}

inline bool chekBool(const string& prompt, const string& error, function<bool(bool)> customCheck = [](bool x) { return true; }) {
    cout << prompt + ": ";

    bool n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}
inline char chekChar(const string& prompt, const string& error, function<bool(char)> customCheck = [](char x) { return true; }) {
    cout << prompt + ": ";

    char n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}
