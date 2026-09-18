#pragma once

class Vehicle;
class Car;
class Truck;
class Customer;
template<typename T>
class SalesReport;

extern vector<Vehicle*> vehicles;
extern vector<Customer*> customers;
extern vector<SalesReport<Vehicle>*> salesReports;
extern vector<Vehicle*> carModels;
extern vector<Vehicle*> truckModels;
extern void Laba6();

extern void saveInitialData();
extern void loadInitialData();
extern void clearInitialData();
extern void addOrder();
extern void displayOrdersInfo();
extern void saveOrdersToFile(const string& filename);
extern void saveReportsToFile(const string& filename);
extern void loadOrdersFromFile(const string& filename);
extern void loadReportsFromFile(const string& filename);
extern void clearAllData();

class Vehicle {
protected:
    string model;
    int cost = 0;
    string vehicleType;
public:
    Vehicle() = default;
    Vehicle(string model, int cost, string vehicleType) : model(model), cost(cost), vehicleType(vehicleType) {}
    Vehicle(const Vehicle& other) = default;
    ~Vehicle() = default;

    void setModel(string model) { this->model = model; }
    void setCost(double cost) { this->cost = cost; }
    void setVehicleType(string vehicleType) { this->vehicleType = vehicleType; }

    string getModel() const { return model; }
    int getCost() const { return cost; }
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

class Car : public Vehicle {
private:
    string carType;
public:
    Car() = default;
    Car(string model, int cost, string carType) : Vehicle(model, cost, "Car"), carType(carType) {}
    Car(const Car& other) = default;
    ~Car() = default;

    void setCarType(string carType) { this->carType = carType; }
    string getCarType() const { return carType; }

    void printInfo() const override {
        cout << model << " - " << cost << " руб (" << carType << ")" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Vehicle::saveToFile(file);
        file << carType << endl;
    }

    void loadFromFile(ifstream& file) override {
        Vehicle::loadFromFile(file);
        getline(file, carType);
    }
};

class Truck : public Vehicle {
private:
    double loadCapacity = 0.0;
public:
    Truck() = default;
    Truck(string model, int cost, double loadCapacity) : Vehicle(model, cost, "Truck"), loadCapacity(loadCapacity) {}
    Truck(const Truck& other) = default;
    ~Truck() = default;

    void setLoadCapacity(double loadCapacity) { this->loadCapacity = loadCapacity; }
    double getLoadCapacity() const { return loadCapacity; }

    void printInfo() const override {
        cout << model << " - " << cost << " руб (" << loadCapacity << " т)" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Vehicle::saveToFile(file);
        file << loadCapacity << endl;
    }

    void loadFromFile(ifstream& file) override {
        Vehicle::loadFromFile(file);
        file >> loadCapacity;
        file.ignore();
    }
};

class Customer {
private:
    string name;
    vector<Vehicle*> orders;
    int totalCost = 0;
public:
    Customer() = default;
    Customer(string name) : name(name) {}
    Customer(const Customer& other) = default;
    ~Customer() = default;

    void setName(string name) { this->name = name; }
    void setOrders(vector<Vehicle*> orders) { this->orders = orders; }
    void setTotalCost(int totalCost) { this->totalCost = totalCost; }

    string getName() const { return name; }
    vector<Vehicle*> getOrders() const { return orders; }
    int getTotalCost() const { return totalCost; }

    void addOrder(Vehicle* vehicle) {
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
            << setw(16) << name.substr(0, 15) << " | "
            << setw(17) << orders.size() << " | "
            << setw(15) << totalCost << " |" << endl;
    }

    static int calculateTotalRevenue(const vector<Customer*>& customers) {
        int revenue = 0;
        for (const auto& customer : customers) {
            revenue += customer->getTotalCost();
        }
        return revenue;
    }

    static int calculateTotalProfit(const vector<Customer*>& customers) {
        int revenue = calculateTotalRevenue(customers);
        return revenue * 0.3;
    }

    static void generateFinancialReport(const vector<Customer*>& customers) {
        if (customers.empty()) {
            cout << "Нет данных для финансового отчета" << endl;
            return;
        }

        int revenue = calculateTotalRevenue(customers);
        int profit = calculateTotalProfit(customers);

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

        for (int i = 0; i < orderCount; i++) {
            string vehicleType;
            getline(file, vehicleType);

            Vehicle* vehicle = nullptr;
            if (vehicleType == "Car") {
                vehicle = new Car();
            }
            else if (vehicleType == "Truck") {
                vehicle = new Truck();
            }

            if (vehicle) {
                vehicle->loadFromFile(file);
                orders.push_back(vehicle);
            }
        }
    }
};

template<typename T>
class SalesReport {
private:
    vector<T*> items;
public:
    SalesReport() = default;
    SalesReport(const SalesReport& other) = default;
    ~SalesReport() = default;

    void setItems(vector<T*> items) { this->items = items; }
    vector<T*> getItems() const { return items; }

    void addItem(T* item) {
        items.push_back(item);
    }

    void generateReport() const {
        if (items.empty()) {
            cout << "Нет данных для отчета" << endl;
            return;
        }

        cout << "=== ОТЧЕТ О ПРОДАЖАХ ===" << endl;
        cout << "Количество проданных единиц: " << items.size() << endl;

        for (int i = 0; i < items.size(); i++) {
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

        for (int i = 0; i < size; i++) {
            string vehicleType;
            getline(file, vehicleType);

            T* item = nullptr;
            if (vehicleType == "Car") {
                item = new Car();
            }
            else if (vehicleType == "Truck") {
                item = new Truck();
            }

            if (item) {
                item->loadFromFile(file);
                items.push_back(item);
            }
        }
    }
};