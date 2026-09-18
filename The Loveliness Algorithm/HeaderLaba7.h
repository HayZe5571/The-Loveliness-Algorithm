#pragma once

class Vehicle_7;
class Car_7;
class Truck_7;
class Customer_7;
template<typename T>
class SalesReport_7;
template<typename T>
class TransactionManager_7;

extern vector<shared_ptr<Vehicle_7>> vehicles_7;
extern vector<shared_ptr<Customer_7>> customers_7;
extern vector<shared_ptr<SalesReport_7<Vehicle_7>>> salesReports_7;
extern vector<shared_ptr<Vehicle_7>> carModels_7;
extern vector<shared_ptr<Vehicle_7>> truckModels_7;
extern vector<shared_ptr<TransactionManager_7<Vehicle_7>>> transactionManagers_7;

extern void Laba7();
extern void saveInitialData_7();
extern void loadInitialData_7();
extern void clearInitialData_7();
extern void addOrder_7();
extern void addVehicleWithTransaction_7();
extern void displayOrdersInfo_7();
extern void saveOrdersToFile_7(const string& filename);
extern void saveReportsToFile_7(const string& filename);
extern void loadOrdersFromFile_7(const string& filename);
extern void loadReportsFromFile_7(const string& filename);
extern void clearAllData_7();

class Vehicle_7 {
protected:
    string model;
    double cost;
    string vehicleType;
public:
    Vehicle_7() : model(""), cost(0), vehicleType("") {}
    Vehicle_7(string model, double cost, string vehicleType)
        : model(model), cost(cost), vehicleType(vehicleType) {
    }
    Vehicle_7(const Vehicle_7& other)
        : model(other.model), cost(other.cost), vehicleType(other.vehicleType) {
    }
    virtual ~Vehicle_7() = default;

    void setModel(string model) { this->model = model; }
    void setCost(double cost) { this->cost = cost; }
    void setVehicleType(string vehicleType) { this->vehicleType = vehicleType; }

    string getModel() const { return model; }
    double getCost() const { return cost; }
    string getVehicleType() const { return vehicleType; }

    virtual void printInfo() const {
        cout << model << " - " << cost << " руб (" << vehicleType << ")" << endl;
    }

    virtual void saveToFile(ofstream& file) const {
        file << vehicleType << endl << model << endl << cost << endl;
    }

    virtual void loadFromFile(ifstream& file) {
        getline(file, vehicleType);
        getline(file, model);
        file >> cost;
        file.ignore();
    }
};

class Car_7 : public Vehicle_7 {
private:
    string carType;
public:
    Car_7() : Vehicle_7(), carType("") {}
    Car_7(string model, double cost, string carType)
        : Vehicle_7(model, cost, "Car_7"), carType(carType) {
    }
    Car_7(const Car_7& other) : Vehicle_7(other), carType(other.carType) {}
    ~Car_7() override = default;

    void setCarType(string carType) { this->carType = carType; }
    string getCarType() const { return carType; }

    void printInfo() const override {
        cout << model << " - " << cost << " руб (" << carType << ")" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Vehicle_7::saveToFile(file);
        file << carType << endl;
    }

    void loadFromFile(ifstream& file) override {
        Vehicle_7::loadFromFile(file);
        getline(file, carType);
    }
};

class Truck_7 : public Vehicle_7 {
private:
    double loadCapacity;
public:
    Truck_7() : Vehicle_7(), loadCapacity(0) {}
    Truck_7(string model, double cost, double loadCapacity)
        : Vehicle_7(model, cost, "Truck_7"), loadCapacity(loadCapacity) {
    }
    Truck_7(const Truck_7& other) : Vehicle_7(other), loadCapacity(other.loadCapacity) {}
    ~Truck_7() override = default;

    void setLoadCapacity(double loadCapacity) { this->loadCapacity = loadCapacity; }
    double getLoadCapacity() const { return loadCapacity; }

    void printInfo() const override {
        cout << model << " - " << cost << " руб (" << loadCapacity << " т)" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Vehicle_7::saveToFile(file);
        file << loadCapacity << endl;
    }

    void loadFromFile(ifstream& file) override {
        Vehicle_7::loadFromFile(file);
        file >> loadCapacity;
        file.ignore();
    }
};

class Customer_7 {
private:
    string name;
    vector<shared_ptr<Vehicle_7>> orders;
    double totalCost;
public:
    Customer_7() : name(""), totalCost(0) {}
    Customer_7(string name) : name(name), totalCost(0) {}
    Customer_7(const Customer_7& other)
        : name(other.name), orders(other.orders), totalCost(other.totalCost) {
    }
    ~Customer_7() = default;

    void setName(string name) { this->name = name; }
    void setOrders(const vector<shared_ptr<Vehicle_7>>& orders) {
        this->orders = orders;
        totalCost = 0;
        for (const auto& v : orders) totalCost += v->getCost();
    }
    void setTotalCost(double totalCost) { this->totalCost = totalCost; }

    string getName() const { return name; }
    vector<shared_ptr<Vehicle_7>> getOrders() const { return orders; }
    double getTotalCost() const { return totalCost; }

    void addOrder(shared_ptr<Vehicle_7> vehicle) {
        orders.push_back(vehicle);
        totalCost += vehicle->getCost();
    }

    void input() {
        cout << "Введите имя заказчика: ";
        getline(cin, name);
    }

    void printInfo() const {
        cout << "Заказчик: " << name << endl;
        cout << "Общая стоимость: " << totalCost << " руб" << endl;
        cout << "Заказанные транспортные средства:" << endl;
        for (const auto& vehicle : orders) {
            cout << "  - ";
            vehicle->printInfo();
        }
    }

    void printTableRow(int index) const {
        cout << "| " << setw(3) << index << " | "
            << setw(16) << (name.length() > 15 ? name.substr(0, 13) + ".." : name) << " | "
            << setw(17) << orders.size() << " | "
            << setw(15) << totalCost << " |" << endl;
    }

    static double calculateTotalRevenue(const vector<shared_ptr<Customer_7>>& customers) {
        double revenue = 0;
        for (const auto& customer : customers) {
            revenue += customer->getTotalCost();
        }
        return revenue;
    }

    static double calculateTotalProfit(const vector<shared_ptr<Customer_7>>& customers) {
        double revenue = calculateTotalRevenue(customers);
        return revenue * 0.3;
    }

    static void generateFinancialReport(const vector<shared_ptr<Customer_7>>& customers) {
        if (customers.empty()) {
            cout << "Нет данных для финансового отчета" << endl;
            return;
        }

        double revenue = calculateTotalRevenue(customers);
        double profit = calculateTotalProfit(customers);

        cout << "=== ФИНАНСОВЫЙ ОТЧЕТ ===" << endl;
        cout << "Общая выручка: " << revenue << " руб" << endl;
        cout << "Прибыль (30%): " << profit << " руб" << endl;
        cout << "Количество заказчиков: " << customers.size() << endl;
    }

    void saveToFile(ofstream& file) const {
        file << name << endl << totalCost << endl;
        file << orders.size() << endl;
        for (const auto& vehicle : orders) {
            vehicle->saveToFile(file);
        }
    }

    void loadFromFile(ifstream& file) {
        getline(file, name);
        file >> totalCost;
        file.ignore();

        int orderCount;
        file >> orderCount;
        file.ignore();

        orders.clear();
        for (int i = 0; i < orderCount; i++) {
            string vehicleType;
            getline(file, vehicleType);

            shared_ptr<Vehicle_7> vehicle;
            if (vehicleType == "Car_7") {
                vehicle = make_shared<Car_7>();
            }
            else if (vehicleType == "Truck_7") {
                vehicle = make_shared<Truck_7>();
            }

            if (vehicle) {
                vehicle->loadFromFile(file);
                orders.push_back(vehicle);
            }
        }
    }
};

template<typename T>
class SalesReport_7 {
private:
    vector<shared_ptr<T>> items;
public:
    SalesReport_7() = default;
    SalesReport_7(const SalesReport_7& other) : items(other.items) {}
    ~SalesReport_7() = default;

    void setItems(const vector<shared_ptr<T>>& items) { this->items = items; }
    vector<shared_ptr<T>> getItems() const { return items; }

    void addItem(shared_ptr<T> item) {
        items.push_back(item);
    }

    void generateReport() const {
        if (items.empty()) {
            cout << "Нет данных для отчета" << endl;
            return;
        }

        cout << "=== ОТЧЕТ О ПРОДАЖАХ ===" << endl;
        cout << "Количество проданных единиц: " << items.size() << endl;

        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". ";
            items[i]->printInfo();
        }
    }

    void saveToFile(ofstream& file) const {
        file << items.size() << endl;
        for (const auto& item : items) {
            item->saveToFile(file);
        }
    }

    void loadFromFile(ifstream& file) {
        int size;
        file >> size;
        file.ignore();

        items.clear();
        for (int i = 0; i < size; i++) {
            string vehicleType;
            getline(file, vehicleType);

            shared_ptr<T> item;
            if (vehicleType == "Car_7") {
                item = make_shared<Car_7>();
            }
            else if (vehicleType == "Truck_7") {
                item = make_shared<Truck_7>();
            }

            if (item) {
                item->loadFromFile(file);
                items.push_back(item);
            }
        }
    }
};

template<typename T>
class TransactionManager_7 {
private:
    shared_ptr<T> currentState;
    shared_ptr<T> previousState;
    bool transactionActive;

public:
    TransactionManager_7() : transactionActive(false) {}
    TransactionManager_7(shared_ptr<T> obj) : currentState(obj), transactionActive(false) {}
    TransactionManager_7(const TransactionManager_7& other)
        : currentState(other.currentState), previousState(other.previousState),
        transactionActive(other.transactionActive) {
    }
    ~TransactionManager_7() = default;

    void setCurrentState(shared_ptr<T> state) { currentState = state; }
    shared_ptr<T> getCurrentState() const { return currentState; }

    bool beginTransaction() {
        if (transactionActive) {
            cout << "Транзакция уже активна!" << endl;
            return false;
        }
        if (!currentState) {
            cout << "Нет объекта для транзакции!" << endl;
            return false;
        }

        previousState = make_shared<T>(*currentState);
        transactionActive = true;
        cout << "Транзакция начата" << endl;
        return true;
    }

    bool commit() {
        if (!transactionActive) {
            cout << "Нет активной транзакции!" << endl;
            return false;
        }

        previousState.reset();
        transactionActive = false;
        cout << "Транзакция зафиксирована" << endl;
        return true;
    }

    bool rollback() {
        if (!transactionActive || !previousState) {
            cout << "Нет активной транзакции для отката!" << endl;
            return false;
        }

        currentState = make_shared<T>(*previousState);
        previousState.reset();
        transactionActive = false;
        cout << "Транзакция отменена (откат)" << endl;
        return true;
    }

    bool isTransactionActive() const { return transactionActive; }

    void showStates() const {
        cout << "Текущее состояние: ";
        if (currentState) {
            currentState->printInfo();
        }
        else {
            cout << "NULL" << endl;
        }

        cout << "Предыдущее состояние: ";
        if (previousState) {
            previousState->printInfo();
        }
        else {
            cout << "NULL" << endl;
        }

        cout << "Транзакция активна: " << (transactionActive ? "Да" : "Нет") << endl;
    }
};