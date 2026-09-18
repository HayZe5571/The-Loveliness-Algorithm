#include "MyIncludes.h"
#include "HeaderLaba6.h"

void saveInitialData() {
    // Создаем файл cars.txt (35 легковых Mercedes)
    ofstream carsFile("cars.txt");
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
        cout << "Файл cars.txt создан (35 моделей)" << endl;
    }

    // Создаем файл trucks.txt (15 грузовиков Mercedes)
    ofstream trucksFile("trucks.txt");
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
        cout << "Файл trucks.txt создан (15 моделей)" << endl;
    }

    cout << "Всего создано 50 моделей Mercedes!" << endl;
}

void loadInitialData() {
    ifstream carsFile("cars.txt");
    if (carsFile.is_open()) {
        string line;
        while (getline(carsFile, line)) {
            stringstream ss(line);
            string model, costStr, carType;

            if (getline(ss, model, ',') && getline(ss, costStr, ',') && getline(ss, carType)) {
                double cost = stod(costStr);
                carModels.push_back(new Car(model, cost, carType));
            }
        }
        carsFile.close();
    }

    ifstream trucksFile("trucks.txt");
    if (trucksFile.is_open()) {
        string line;
        while (getline(trucksFile, line)) {
            stringstream ss(line);
            string model, costStr, capacityStr;

            if (getline(ss, model, ',') && getline(ss, costStr, ',') && getline(ss, capacityStr)) {
                double cost = stod(costStr);
                double capacity = stod(capacityStr);
                truckModels.push_back(new Truck(model, cost, capacity));
            }
        }
        trucksFile.close();
    }
}

void clearInitialData() {
    for (Vehicle* vehicle : carModels) delete vehicle;
    for (Vehicle* vehicle : truckModels) delete vehicle;
    carModels.clear();
    truckModels.clear();
}

vector<string> Split(const string& str, char delimiter) {
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

void addOrder() {
    cout << "\n=== ОФОРМЛЕНИЕ ЗАКАЗА ===" << endl;

    Customer* customer = new Customer();
    customer->input();

    cout << "\nДоступные легковые автомобили:" << endl;
    for (int i = 0; i < carModels.size(); i++) {
        cout << i + 1 << ". ";
        carModels[i]->printInfo();
    }

    cout << "\nДоступные грузовики:" << endl;
    for (int i = 0; i < truckModels.size(); i++) {
        cout << i + 1 + carModels.size() << ". ";
        truckModels[i]->printInfo();
    }

    cout << "Введите номера выбранных моделей через запятую: ";
    string selectedModelsInput;
    getline(cin, selectedModelsInput);

    vector<string> selectedNumbers = Split(selectedModelsInput, ',');

    for (const string& numStr : selectedNumbers) {
        int num = stoi(numStr);
        if (num >= 1 && num <= carModels.size() + truckModels.size()) {
            if (num <= carModels.size()) {
                // Легковой автомобиль
                Car* originalCar = dynamic_cast<Car*>(carModels[num - 1]);
                Car* orderedCar = new Car(originalCar->getModel(), originalCar->getCost(), originalCar->getCarType());
                customer->addOrder(orderedCar);
                vehicles.push_back(orderedCar);
            }
            else {
                // Грузовик
                int truckIndex = num - carModels.size() - 1;
                Truck* originalTruck = dynamic_cast<Truck*>(truckModels[truckIndex]);
                Truck* orderedTruck = new Truck(originalTruck->getModel(), originalTruck->getCost(), originalTruck->getLoadCapacity());
                customer->addOrder(orderedTruck);
                vehicles.push_back(orderedTruck);
            }
        }
    }

    customers.push_back(customer);
    cout << "Заказ оформлен! Общая стоимость: " << customer->getTotalCost() << " руб" << endl;
}

void displayOrdersInfo() {
    if (customers.empty()) {
        cout << "Нет данных о заказах!" << endl;
        return;
    }

    cout << "\n=== ИНФОРМАЦИЯ О ЗАКАЗАХ ===" << endl;
    cout << "+-----+------------------+-------------------+-----------------+" << endl;
    cout << "|  №  |     Заказчик     | Кол-во транспорта | Общая стоимость |" << endl;
    cout << "+-----+------------------+-------------------+-----------------+" << endl;

    for (int i = 0; i < customers.size(); i++) {
        customers[i]->printTableRow(i + 1);
    }

    cout << "+-----+------------------+-------------------+-----------------+" << endl;
    cout << "Всего заказчиков: " << customers.size() << endl;

    Customer::generateFinancialReport(customers);

    cout << "\n=== ДЕТАЛЬНАЯ ИНФОРМАЦИЯ ===" << endl;
    for (int i = 0; i < customers.size(); i++) {
        cout << "\nЗаказчик " << i + 1 << ":" << endl;
        customers[i]->printInfo();
    }

    cout << "\n=== ОТЧЕТ ПО ПРОДАННЫМ ТРАНСПОРТНЫМ СРЕДСТВАМ ===" << endl;
    SalesReport<Vehicle> salesReport;
    for (Customer* customer : customers) {
        for (Vehicle* vehicle : customer->getOrders()) {
            salesReport.addItem(vehicle);
        }
    }
    salesReport.generateReport();
}

void saveOrdersToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    file << customers.size() << endl;
    for (Customer* customer : customers) {
        customer->saveToFile(file);
    }

    file.close();
    cout << "Данные о заказах сохранены в " << filename << endl;
}

void saveReportsToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    file << salesReports.size() << endl;
    for (SalesReport<Vehicle>* report : salesReports) {
        report->saveToFile(file);
    }

    file.close();
    cout << "Отчеты сохранены в " << filename << endl;
}

void loadOrdersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    for (Customer* customer : customers) delete customer;
    customers.clear();

    int customerCount;
    file >> customerCount;
    file.ignore();

    for (int i = 0; i < customerCount; i++) {
        Customer* customer = new Customer();
        customer->loadFromFile(file);
        customers.push_back(customer);
    }

    file.close();
    cout << "Данные о заказах загружены из " << filename << endl;
}

void loadReportsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }

    for (SalesReport<Vehicle>* report : salesReports) delete report;
    salesReports.clear();

    int reportCount;
    file >> reportCount;
    file.ignore();

    for (int i = 0; i < reportCount; i++) {
        SalesReport<Vehicle>* report = new SalesReport<Vehicle>();
        report->loadFromFile(file);
        salesReports.push_back(report);
    }

    file.close();
    cout << "Отчеты загружены из " << filename << endl;
}

void clearAllData() {
    if (customers.empty() && salesReports.empty()) {
        cout << "\nНет данных для очистки!" << endl;
        return;
    }

    bool confirm = danetka("Вы уверены, что хотите удалить все данные");
    if (!confirm) {
        cout << "Очистка отменена" << endl;
        return;
    }

    for (Customer* customer : customers) delete customer;
    for (SalesReport<Vehicle>* report : salesReports) delete report;
    for (Vehicle* vehicle : vehicles) delete vehicle;
    customers.clear();
    salesReports.clear();
    vehicles.clear();
    cout << "Все данные удалены!" << endl;
}