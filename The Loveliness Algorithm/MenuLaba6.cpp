// Разработать набор классов(минимум 5) по теме «Машиностроительное предприятие». Корректно
// реализовать связи между классами. В разработанном наборе классов должен быть хотя бы один
// шаблонный класс. Все классы должны иметь методы получения и установки значений полей.
// Программа должна обеспечивать вывод детальной информации о созданной продукции, итоговой
// сумме в табличном виде на экран и в файл. Использовать конструктор с параметрами,
// конструктор без параметров, конструктор копирования, деструктор.

#include "MyIncludes.h"
#include "HeaderLaba6.h"

vector<Vehicle*> vehicles;
vector<Customer*> customers;
vector<SalesReport<Vehicle>*> salesReports;
vector<Vehicle*> carModels;
vector<Vehicle*> truckModels;

void Laba6() {
    saveInitialData();
    loadInitialData();

    int choice;
    do {
        cout << "========== МАШИНОСТРОИТЕЛЬНОЕ ПРЕДПРИЯТИЕ MERCEDES ==========" << endl;
        cout << "1. Оформить заказ" << endl;
        cout << "2. Показать информацию о заказах" << endl;
        cout << "3. Сохранить данные в файл" << endl;
        cout << "4. Загрузить данные из файла" << endl;
        cout << "5. Очистить все данные" << endl;
        cout << "6. Выход в главное меню" << endl;

        choice = chek<int>("Выберите пункт", "Неверный выбор", [](int x) { return x >= 1 && x <= 6; });

        switch (choice) {
        case 1: addOrder(); break;
        case 2: displayOrdersInfo(); break;
        case 3:
            saveOrdersToFile("orders_data.txt");
            saveReportsToFile("reports_data.txt");
            break;
        case 4:
            loadOrdersFromFile("orders_data.txt");
            loadReportsFromFile("reports_data.txt");
            break;
        case 5: clearAllData(); break;
        case 6: cout << "Возврат в главное меню..." << endl; break;
        }
        cout << endl;

    } while (choice != 6);

    clearInitialData();
}