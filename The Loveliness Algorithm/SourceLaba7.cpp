#include "MyIncludes.h"
#include "HeaderLaba7.h"

extern vector<shared_ptr<Vehicle_7>> vehicles_7;
extern vector<shared_ptr<Customer_7>> customers_7;
extern vector<shared_ptr<SalesReport_7<Vehicle_7>>> salesReports_7;
extern vector<shared_ptr<Vehicle_7>> carModels_7;
extern vector<shared_ptr<Vehicle_7>> truckModels_7;
extern vector<shared_ptr<TransactionManager_7<Vehicle_7>>> transactionManagers_7;

void saveInitialData_7() {
    ofstream carsFile("cars_7.txt");
    if (carsFile.is_open()) {
        carsFile << "G-Class_Розовый_Геленваген,250000,Внедорожник\n";
        carsFile << "G-Class,220000,Внедорожник\n";
        carsFile << "GLE,95000,Внедорожник\n";
        carsFile << "GLC,85000,Внедорожник\n";
        carsFile << "GLB,65000,Внедорожник\n";
        carsFile << "GLA,55000,Кроссовер\n";
        carsFile << "EQS,120000,Электромобиль\n";
        carsFile << "EQE,90000,Электромобиль\n";
        carsFile << "EQB,70000,Электромобиль\n";
        carsFile << "EQA,60000,Электромобиль\n";
        carsFile << "S-Class_Maybach,350000,Люкс\n";
        carsFile << "S-Class,180000,Седан\n";
        carsFile << "E-Class,85000,Седан\n";
        carsFile << "C-Class,65000,Седан\n";
        carsFile << "A-Class,45000,Хэтчбек\n";
        carsFile << "B-Class,40000,Хэтчбек\n";
        carsFile << "CLA,50000,Купе\n";
        carsFile << "CLS,95000,Купе\n";
        carsFile << "AMG_GT,180000,Спорткар\n";
        carsFile << "AMG_C63,120000,Спорткар\n";
        carsFile << "AMG_A45,80000,Спорткар\n";
        carsFile << "AMG_G63,280000,Внедорожник\n";
        carsFile << "AMG_GLE53,130000,Внедорожник\n";
        carsFile << "AMG_GLC43,110000,Кроссовер\n";
        carsFile << "V-Class,70000,Минивэн\n";
        carsFile << "EQV,85000,Электромобиль\n";
        carsFile << "Citan,35000,Фургон\n";
        carsFile << "X-Class,80000,Пикап\n";
        carsFile << "SL_Class,150000,Родстер\n";
        carsFile << "AMG_SL63,220000,Родстер\n";
        carsFile << "CLА_Shooting_Brake,55000,Универсал\n";
        carsFile << "E-Class_All-Terrain,90000,Внедорожник\n";
        carsFile << "AMG_GT_4-Door,160000,Спорткар\n";
        carsFile << "Maybach_GLS,300000,Люкс\n";
        carsFile << "Maybach_S-Class,400000,Люкс\n";
        carsFile.close();
    }

    ofstream trucksFile("trucks_7.txt");
    if (trucksFile.is_open()) {
        trucksFile << "Actros,180000,25.0\n";
        trucksFile << "Arocs,160000,20.0\n";
        trucksFile << "Atego,120000,15.0\n";
        trucksFile << "Econic,90000,10.0\n";
        trucksFile << "Unimog,220000,30.0\n";
        trucksFile << "Antos,140000,18.0\n";
        trucksFile << "Axor,110000,12.0\n";
        trucksFile << "Zetros,190000,22.0\n";
        trucksFile << "Atego_Compact,80000,8.0\n";
        trucksFile << "Econic_HD,100000,11.0\n";
        trucksFile << "Actros_L,200000,28.0\n";
        trucksFile << "Arocs_SLT,170000,21.0\n";
        trucksFile << "Unimog_U500,240000,35.0\n";
        trucksFile << "Econic_Low_Entry,95000,9.5\n";
        trucksFile << "Actros_MP4,185000,26.0\n";
        trucksFile.close();
    }
}

void loadInitialData_7() {
    ifstream carsFile("cars_7.txt");
    if (carsFile.is_open()) {
        string line;
        while (getline(carsFile, line)) {
            stringstream ss(line);
            string model, costStr, carType;

            if (getline(ss, model, ',') && getline(ss, costStr, ',') && getline(ss, carType)) {
                double cost = stod(costStr);
                carModels_7.push_back(make_shared<Car_7>(model, cost, carType));
            }
        }
        carsFile.close();
    }

    ifstream trucksFile("trucks_7.txt");
    if (trucksFile.is_open()) {
        string line;
        while (getline(trucksFile, line)) {
            stringstream ss(line);
            string model, costStr, capacityStr;

            if (getline(ss, model, ',') && getline(ss, costStr, ',') && getline(ss, capacityStr)) {
                double cost = stod(costStr);
                double capacity = stod(capacityStr);
                truckModels_7.push_back(make_shared<Truck_7>(model, cost, capacity));
            }
        }
        trucksFile.close();
    }
}

void clearInitialData_7() {
    carModels_7.clear();
    truckModels_7.clear();
}

vector<string> Split_7(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        tokens.push_back(token);
    }
    return tokens;
}

void addOrder_7() {
    cout << "\n=== ОФОРМЛЕНИЕ ЗАКАЗА (с транзакцией) ===" << endl;

    auto customer = make_shared<Customer_7>();
    customer->input();
     
    auto orderTransaction = make_shared<TransactionManager_7<Customer_7>>(customer);
    orderTransaction->beginTransaction();

    cout << "\nДоступные легковые автомобили:" << endl;
    for (size_t i = 0; i < carModels_7.size(); i++) {
        cout << i + 1 << ". ";
        carModels_7[i]->printInfo();
    }

    cout << "\nДоступные грузовики:" << endl;
    for (size_t i = 0; i < truckModels_7.size(); i++) {
        cout << i + 1 + carModels_7.size() << ". ";
        truckModels_7[i]->printInfo();
    }

    cout << "Введите номера выбранных моделей через запятую: ";
    string selectedModelsInput;
    getline(cin, selectedModelsInput);

    vector<string> selectedNumbers = Split_7(selectedModelsInput, ',');

    double totalCost = 0;
    vector<shared_ptr<Vehicle_7>> selectedVehicles;

    for (const string& numStr : selectedNumbers) {
        try {
            int num = stoi(numStr);

            if (num < 1 || num >(int)(carModels_7.size() + truckModels_7.size())) {
                cout << "Неверный номер: " << num << " - пропускаем" << endl;
                continue;
            }

            shared_ptr<Vehicle_7> orderedVehicle;

            if (num <= (int)carModels_7.size()) {
                auto originalCar = dynamic_pointer_cast<Car_7>(carModels_7[num - 1]);
                orderedVehicle = make_shared<Car_7>(originalCar->getModel(), originalCar->getCost(), originalCar->getCarType());
            }
            else {
                int truckIndex = num - carModels_7.size() - 1;
                auto originalTruck = dynamic_pointer_cast<Truck_7>(truckModels_7[truckIndex]);
                orderedVehicle = make_shared<Truck_7>(originalTruck->getModel(), originalTruck->getCost(), originalTruck->getLoadCapacity());
            }

            selectedVehicles.push_back(orderedVehicle);
            totalCost += orderedVehicle->getCost();

        }
        catch (const exception& e) {
            cout << "Ошибка в номере '" << numStr << "' - пропускаем" << endl;
        }
    }

    if (selectedVehicles.empty()) {
        cout << "Не выбрано ни одной модели!" << endl;
        orderTransaction->rollback();
        return;
    }

    cout << "\n=== ПОДТВЕРЖДЕНИЕ ЗАКАЗА ===" << endl;
    cout << "Заказчик: " << customer->getName() << endl;
    cout << "Выбранные модели (" << selectedVehicles.size() << " шт.):" << endl;

    for (size_t i = 0; i < selectedVehicles.size(); i++) {
        cout << "  " << i + 1 << ". ";
        selectedVehicles[i]->printInfo();
    }

    cout << "Общая стоимость: " << totalCost << " руб" << endl;

    bool confirm = danetka("Подтвердить оформление заказа?");

    if (confirm) {
        for (auto& vehicle : selectedVehicles) {
            customer->addOrder(vehicle);
            vehicles_7.push_back(vehicle);
        }
        customers_7.push_back(customer);
        orderTransaction->commit();
        cout << "Заказ оформлен успешно!" << endl;
    }
    else {
        orderTransaction->rollback();
        cout << "Заказ отменен!" << endl;
    }
}

void addVehicleWithTransaction_7() {
    cout << "\n=== ДОБАВЛЕНИЕ НОВОЙ МОДЕЛИ (с транзакцией) ===" << endl;

    cout << "Выберите тип: 1. Легковой 2. Грузовик" << endl;
    int type = chek<int>("Тип", "1 или 2", [](int x) { return x == 1 || x == 2; });

    cout << "Введите модель: ";
    string model;
    getline(cin, model);

    double cost = chek<double>("Введите цену", "Цена должна быть > 0",
        [](double x) { return x > 0; });

    shared_ptr<Vehicle_7> newVehicle;
    shared_ptr<TransactionManager_7<Vehicle_7>> transaction;

    if (type == 1) {
        cout << "Введите тип кузова: ";
        string carType;
        getline(cin, carType);

        newVehicle = make_shared<Car_7>(model, cost, carType);
    }
    else {
        double capacity = chek<double>("Введите грузоподъемность (т)",
            "Должна быть > 0", [](double x) { return x > 0; });

        newVehicle = make_shared<Truck_7>(model, cost, capacity);
    }

    transaction = make_shared<TransactionManager_7<Vehicle_7>>(newVehicle);
    transaction->beginTransaction();

    cout << "\n=== ПРЕДВАРИТЕЛЬНЫЙ ПРОСМОТР ===" << endl;
    newVehicle->printInfo();

    bool confirm = danetka("Подтвердить добавление этой модели?");

    if (confirm) {
        if (type == 1) {
            carModels_7.push_back(newVehicle);
        }
        else {
            truckModels_7.push_back(newVehicle);
        }
        transaction->commit();
        cout << "Модель добавлена в каталог!" << endl;

        if (type == 1) {
            ofstream carsFile("cars_7.txt", ios::app);
            if (carsFile.is_open()) {
                auto car = dynamic_pointer_cast<Car_7>(newVehicle);
                carsFile << model << "," << cost << "," << car->getCarType() << "\n";
                carsFile.close();
            }
        }
        else {
            ofstream trucksFile("trucks_7.txt", ios::app);
            if (trucksFile.is_open()) {
                auto truck = dynamic_pointer_cast<Truck_7>(newVehicle);
                trucksFile << model << "," << cost << "," << truck->getLoadCapacity() << "\n";
                trucksFile.close();
            }
        }
    }
    else {
        transaction->rollback();
        cout << "Добавление отменено!" << endl;
    }
}

void displayOrdersInfo_7() {
    if (customers_7.empty()) {
        cout << "Нет данных о заказах!" << endl;
        return;
    }

    cout << "\n=== ИНФОРМАЦИЯ О ЗАКАЗАХ (ЛАБА 7) ===" << endl;
    cout << "+-----+------------------+-------------------+-----------------+" << endl;
    cout << "|  №  |     Заказчик     | Кол-во транспорта | Общая стоимость |" << endl;
    cout << "+-----+------------------+-------------------+-----------------+" << endl;

    for (size_t i = 0; i < customers_7.size(); i++) {
        customers_7[i]->printTableRow(i + 1);
    }

    cout << "+-----+------------------+-------------------+-----------------+" << endl;
    cout << "Всего заказчиков: " << customers_7.size() << endl;

    Customer_7::generateFinancialReport(customers_7);

    cout << "\n=== ДЕТАЛЬНАЯ ИНФОРМАЦИЯ ===" << endl;
    for (size_t i = 0; i < customers_7.size(); i++) {
        cout << "\nЗаказчик " << i + 1 << ":" << endl;
        customers_7[i]->printInfo();
    }

    cout << "\n=== ОТЧЕТ ПО ПРОДАННЫМ ТРАНСПОРТНЫМ СРЕДСТВАМ ===" << endl;
    auto salesReport = make_shared<SalesReport_7<Vehicle_7>>();
    for (const auto& customer : customers_7) {
        for (const auto& vehicle : customer->getOrders()) {
            salesReport->addItem(vehicle);
        }
    }
    salesReport->generateReport();
    salesReports_7.push_back(salesReport);
}

void saveOrdersToFile_7(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    file << customers_7.size() << endl;
    for (const auto& customer : customers_7) {
        customer->saveToFile(file);
    }

    file.close();
    cout << "Данные о заказах сохранены в " << filename << endl;
}

void saveReportsToFile_7(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    file << salesReports_7.size() << endl;
    for (const auto& report : salesReports_7) {
        report->saveToFile(file);
    }

    file.close();
    cout << "Отчеты сохранены в " << filename << endl;
}

void loadOrdersFromFile_7(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    customers_7.clear();

    int customerCount;
    file >> customerCount;
    file.ignore();

    for (int i = 0; i < customerCount; i++) {
        auto customer = make_shared<Customer_7>();
        customer->loadFromFile(file);
        customers_7.push_back(customer);
    }

    file.close();
    cout << "Данные о заказах загружены из " << filename << endl;
}

void loadReportsFromFile_7(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    salesReports_7.clear();

    int reportCount;
    file >> reportCount;
    file.ignore();

    for (int i = 0; i < reportCount; i++) {
        auto report = make_shared<SalesReport_7<Vehicle_7>>();
        report->loadFromFile(file);
        salesReports_7.push_back(report);
    }

    file.close();
    cout << "Отчеты загружены из " << filename << endl;
}

void clearAllData_7() {
    if (customers_7.empty() && salesReports_7.empty() && transactionManagers_7.empty()) {
        cout << "\nНет данных для очистки!" << endl;
        return;
    }

    bool confirm = danetka("Вы уверены, что хотите удалить все данные");
    if (!confirm) {
        cout << "Очистка отменена" << endl;
        return;
    }

    customers_7.clear();
    salesReports_7.clear();
    vehicles_7.clear();
    transactionManagers_7.clear();

    cout << "Все данные удалены!" << endl;
}