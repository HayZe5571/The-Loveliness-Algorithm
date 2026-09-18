#pragma once
#define PI 3.14159265358979323846

class FlatFigure;
class Circle;
class Rectangleу;

extern vector<FlatFigure*> shapes;
extern void Laba4();

extern void addShape();
extern void displayAllShapes();
extern void saveToFileShapes(const string& filename);
extern void loadFromFileShapes(const string& filename);
extern void clearShapes();

class FlatFigure {
protected:
    string color;
    string name;
    string material;

public:
    FlatFigure() = default;
    FlatFigure(string color, string name, string material)
        : color(color), name(name), material(material) { }
    FlatFigure(const FlatFigure& other) = default;
    virtual ~FlatFigure() = default;

    void setColor(const string& color) { this->color = color; }
    void setName(const string& name) { this->name = name; }
    void setMaterial(const string& material) { this->material = material; }

    string getColor() const { return color; }
    string getName() const { return name; }
    string getMaterial() const { return material; }

    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual string getType() const = 0;
    virtual string getSize() const = 0;

    virtual void input() {
        cout << "Введите цвет фигуры: ";
        getline(cin, color);
        cout << "Введите название фигуры: ";
        getline(cin, name);
        cout << "Введите материал фигуры: ";
        getline(cin, material);
    }
    virtual void printInfo(int index) const {
        cout << "| " << setw(3) << index + 1 << " | "
            << setw(15) << name.substr(0, 14) << " | "
            << setw(12) << getType().substr(0, 11) << " | "
            << setw(12) << getSize().substr(0, 11) << " | "
            << setw(12) << color.substr(0, 11) << " | "
            << setw(12) << material.substr(0, 11) << " | ";
    }

    virtual void saveToFile(ofstream& file) const = 0;
    virtual void loadFromFile(ifstream& file) = 0;

    static void printTableHeader() {
        cout << "+-----+-----------------+--------------+--------------+--------------+--------------+--------------+------------------+" << endl;
        cout << "|  №  |     Название    |     Тип      |    Размер    |     Цвет     |   Материал   |   Площадь    |    Периметр      |" << endl;
        cout << "+-----+-----------------+--------------+--------------+--------------+--------------+--------------+------------------+" << endl;
    }
    static void printTableFooter() {
        cout << "+-----+-----------------+--------------+--------------+--------------+--------------+--------------+------------------+" << endl;
    }
};

class Circle : public FlatFigure {
private:
    double radius = 0;

public:
    Circle() = default;
    Circle(double radius, string color, string name, string material)
        : FlatFigure(color, name, material), radius(radius) { }
    Circle(const Circle& other) = default;
    ~Circle() override = default;

    void setRadius(double radius) { this->radius = radius; }
    double getRadius() const { return radius; }
    string getType() const override { return "Круг"; }
    string getSize() const override { return "r=" + to_string(radius).substr(0, 4); }

    double calculateArea() const override { return PI * radius * radius; }
    double calculatePerimeter() const override { return 2 * PI * radius; }

    void input() override {
        FlatFigure::input();
        radius = chekDouble("Введите радиус окружности", "Радиус должен быть положительным", [](double x) { return x > 0; });
    }
    void printInfo(int index) const override {
        FlatFigure::printInfo(index);
        cout << setw(12) << fixed << setprecision(2) << calculateArea() << " | "
            << setw(16) << fixed << setprecision(2) << calculatePerimeter() << " |"
            << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "CIRCLE" << endl;
        file << color << endl << name << endl << material << endl << radius << endl;
    }
    void loadFromFile(ifstream& file) override {
        getline(file, color);
        getline(file, name);
        getline(file, material);
        file >> radius;
        file.ignore();
    }
};

class Rectangleу : public FlatFigure {
private:
    double length = 0;
    double width = 0;

public:
    Rectangleу() = default;
    Rectangleу(double length, double width, string color, string name, string material)
        : FlatFigure(color, name, material), length(length), width(width) { }
    Rectangleу(const Rectangleу& other) = default;
    ~Rectangleу() override = default;

    void setLength(double length) { this->length = length; }
    void setWidth(double width) { this->width = width; }
    double getLength() const { return length; }
    double getWidth() const { return width; }
    string getType() const override {
        if (length == width) return "Квадрат";
        return "Прямоугольник";
    }
    string getSize() const override { return to_string(length).substr(0, 4) + "x" + to_string(width).substr(0, 4); }

    double calculateArea() const override { return length * width; }
    double calculatePerimeter() const override { return 2 * (length + width); }

    void input() override {
        FlatFigure::input();
        length = chekDouble("Введите длину прямоугольника", "Длина должна быть положительной", [](double x) { return x > 0; });
        width = chekDouble("Введите ширину прямоугольника", "Ширина должна быть положительной", [](double x) { return x > 0; });
    }
    void printInfo(int index) const override {
        FlatFigure::printInfo(index);
        cout << setw(12) << fixed << setprecision(2) << calculateArea() << " | "
            << setw(16) << fixed << setprecision(2) << calculatePerimeter() << " |"
            << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "RECTANGLE" << endl;
        file << color << endl << name << endl << material << endl << length << endl << width << endl;
    }
    void loadFromFile(ifstream& file) override {
        getline(file, color);
        getline(file, name);
        getline(file, material);
        file >> length >> width;
        file.ignore();
    }
};