// Разработать набор классов(минимум 5) по теме «Машиностроительное предприятие».Корректно реализовать связи между классами.
// Использовать smart - указатели для создания программы учета продаваемых и закупаемых деталей на машиностроительном предприятии.
// Реализовать механизм транзакций, который позволит откатывать изменения, если данные о продукции введены неверно(например, цена 
// или количество имеют некорректное значение).В разработанном наборе классов должен быть хотя бы один шаблонный класс.Все классы 
// должны иметь методы получения и установки значений полей.Программа должна обеспечивать вывод детальной информации о созданной 
// продукции, итоговой сумме в табличном виде на экран и в файл.Использовать конструктор с параметрами, конструктор без параметров, 
// конструктор копирования, деструктор.

#include "MyIncludes.h"
#include "HeaderLaba7.h"

vector<shared_ptr<Vehicle_7>> vehicles_7;
vector<shared_ptr<Customer_7>> customers_7;
vector<shared_ptr<SalesReport_7<Vehicle_7>>> salesReports_7;
vector<shared_ptr<Vehicle_7>> carModels_7;
vector<shared_ptr<Vehicle_7>> truckModels_7;
vector<shared_ptr<TransactionManager_7<Vehicle_7>>> transactionManagers_7;

void Laba7() {
    saveInitialData_7();
    loadInitialData_7();

    int choice;
    do {
        cout << "\n========== МАШИНОСТРОИТЕЛЬНОЕ ПРЕДПРИЯТИЕ MERCEDES ==========" << endl;
        cout << "1. Оформить заказ (с транзакцией)" << endl;
        cout << "2. Добавить новую модель (с транзакцией)" << endl;
        cout << "3. Показать информацию о заказах" << endl;
        cout << "4. Сохранить данные в файл" << endl;
        cout << "5. Загрузить данные из файл" << endl;
        cout << "6. Очистить все данные" << endl;
        cout << "7. Выход в главное меню" << endl;

        choice = chek<int>("Выберите пункт", "Неверный выбор", [](int x) { return x >= 1 && x <= 7; });

        switch (choice) {
        case 1: addOrder_7(); break;
        case 2: addVehicleWithTransaction_7(); break;
        case 3: displayOrdersInfo_7(); break;
        case 4:
            saveOrdersToFile_7("orders_data_7.txt");
            saveReportsToFile_7("reports_data_7.txt");
            break;
        case 5:
            loadOrdersFromFile_7("orders_data_7.txt");
            loadReportsFromFile_7("reports_data_7.txt");
            break;
        case 6: clearAllData_7(); break;
        case 7: cout << "Возврат в главное меню..." << endl; break;
        }
        cout << endl;

    } while (choice != 7);

    clearInitialData_7();
}