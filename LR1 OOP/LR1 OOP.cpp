#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>

using namespace std;

// Определение M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Абстрактный базовый класс
class Shape {
protected:
    string color;
    static int totalShapes; // Счетчик созданных фигур

public:
    // Конструктор по умолчанию
    Shape() : color("black") {
        totalShapes++;
        cout << "Вызван конструктор по умолчанию класса Shape. Цвет: " << color << endl;
    }

    // Конструктор с параметрами
    Shape(const string& c) : color(c) {
        totalShapes++;
        cout << "Вызван конструктор с параметрами класса Shape. Цвет: " << color << endl;
    }

    // Конструктор копирования
    Shape(const Shape& other) : color(other.color) {
        totalShapes++;
        cout << "Вызван конструктор копирования класса Shape. Цвет: " << color << endl;
    }

    // Виртуальный деструктор
    virtual ~Shape() {
        totalShapes--;
        cout << "Вызван деструктор класса Shape. Цвет: " << color << endl;
    }

    // Чисто виртуальные методы (абстрактные)
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    // Виртуальный метод
    virtual void displayInfo() const {
        cout << "Shape Info - Цвет: " << color << endl;
    }

    // Виртуальный метод масштабирования (добавлен в базовый класс)
    virtual void scale(double factor) {
        cout << "Внимание: метод scale() не определен для этой фигуры" << endl;
    }

    // Перегруженный метод
    void setColor(const string& c) { color = c; }
    string getColor() const { return color; }

    // Статический метод для получения количества фигур
    static int getTotalShapes() { return totalShapes; }
};

// Инициализация статического члена
int Shape::totalShapes = 0;

// Класс-потомок 1: Circle
class Circle : public Shape {
private:
    double radius;

public:
    // Конструктор по умолчанию
    Circle() : Shape(), radius(1.0) {
        cout << "Вызван конструктор по умолчанию класса Circle. Радиус: " << radius << endl;
    }

    // Конструктор с параметрами
    Circle(const string& c, double r) : Shape(c), radius(r) {
        cout << "Вызван конструктор с параметрами класса Circle. Радиус: " << radius << endl;
    }

    // Конструктор копирования
    Circle(const Circle& other) : Shape(other), radius(other.radius) {
        cout << "Вызван конструктор копирования класса Circle. Радиус: " << radius << endl;
    }

    // Деструктор
    ~Circle() override {
        cout << "Вызван деструктор класса Circle. Радиус: " << radius << endl;
    }

    // Переопределение виртуальных методов
    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }

    // Переопределение виртуального метода с дополнительной информацией
    void displayInfo() const override {
        Shape::displayInfo();
        cout << "Circle Info - Радиус: " << radius
            << ", Площадь: " << area()
            << ", Периметр: " << perimeter() << endl;
    }

    // Переопределение виртуального метода scale
    void scale(double factor) override {
        radius *= factor;
        cout << "К окружности было применено масштабирование с коэффициентом: " << factor << ". Новый радиус: " << radius << endl;
    }

    // Перегруженные методы
    void setRadius(double r) { radius = r; }
    double getRadius() const { return radius; }

    // Перегруженный метод с тем же именем, но другими параметрами
    void scale(int factor) {
        radius *= factor;
        cout << "К окружности было применено масштабирование с целочисленным коэффициентом: " << factor << ". Новый радиус: " << radius << endl;
    }
};

// Класс-потомок 2: Rectangle
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    // Конструктор по умолчанию
    Rectangle() : Shape(), width(1.0), height(1.0) {
        cout << "Вызван конструктор по умолчанию класса Rectangle. Ширина: " << width << ", Высота: " << height << endl;
    }

    // Конструктор с параметрами
    Rectangle(const string& c, double w, double h) : Shape(c), width(w), height(h) {
        cout << "Вызван конструктор с параметрами класса Rectangle. Ширина: " << width << ", Высота: " << height << endl;
    }

    // Конструктор копирования
    Rectangle(const Rectangle& other) : Shape(other), width(other.width), height(other.height) {
        cout << "Вызван конструктор копирования класса Rectangle. Ширина: " << width << ", Высота: " << height << endl;
    }

    // Деструктор
    ~Rectangle() override {
        cout << "Вызван деструктор класса Rectangle. Ширина: " << width << ", Высота: " << height << endl;
    }

    // Переопределение виртуальных методов
    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void displayInfo() const override {
        Shape::displayInfo();
        cout << "Rectangle Info - Ширина: " << width << ", Высота: " << height
            << ", Площадь: " << area() << ", Периметр: " << perimeter() << endl;
    }

    // Переопределение виртуального метода scale
    void scale(double factor) override {
        width *= factor;
        height *= factor;
        cout << "К прямоугольнику было применено масштабирование с коэффициентом: " << factor
            << ". Новые размеры: " << width << " x " << height << endl;
    }

    // Собственные методы
    void setDimensions(double w, double h) { width = w; height = h; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

// Класс-потомок 3: Triangle
class Triangle : public Shape {
private:
    double sideA;
    double sideB;
    double sideC;

public:
    // Конструктор по умолчанию
    Triangle() : Shape(), sideA(3.0), sideB(4.0), sideC(5.0) {
        cout << "Вызван конструктор по умолчанию класса Triangle. Длины сторон: " << sideA << ", " << sideB << ", " << sideC << endl;
    }

    // Конструктор с параметрами
    Triangle(const string& c, double a, double b, double cSide) : Shape(c), sideA(a), sideB(b), sideC(cSide) {
        cout << "Вызван конструктор с параметрами класса Triangle. Длины сторон: " << sideA << ", " << sideB << ", " << sideC << endl;
    }

    // Конструктор копирования
    Triangle(const Triangle& other) : Shape(other), sideA(other.sideA), sideB(other.sideB), sideC(other.sideC) {
        cout << "Вызван конструктор копирования класса Triangle. Длины сторон: " << sideA << ", " << sideB << ", " << sideC << endl;
    }

    // Деструктор
    ~Triangle() override {
        cout << "Вызван деструктор класса Triangle. Длины сторон: " << sideA << ", " << sideB << ", " << sideC << endl;
    }

    // Переопределение виртуальных методов
    double area() const override {
        // Формула Герона
        double s = (sideA + sideB + sideC) / 2;
        return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    }

    double perimeter() const override {
        return sideA + sideB + sideC;
    }

    void displayInfo() const override {
        Shape::displayInfo();
        cout << "Triangle Info - Длины сторон: " << sideA << ", " << sideB << ", " << sideC
            << ", Площадь: " << area() << ", Периметр: " << perimeter() << endl;
    }

    // Переопределение виртуального метода scale
    void scale(double factor) override {
        sideA *= factor;
        sideB *= factor;
        sideC *= factor;
        cout << "К треугольнику было применено масштабирование с коэффициентом: " << factor
            << ". Новые длины сторон: " << sideA << ", " << sideB << ", " << sideC << endl;
    }

    // Проверка существования треугольника
    bool isValid() const {
        return (sideA + sideB > sideC) &&
            (sideA + sideC > sideB) &&
            (sideB + sideC > sideA);
    }
};

// Класс-потомок 4: Square (наследуется от Rectangle)
class Square : public Rectangle {
private:
    // Специфичное для квадрата свойство
    bool isRegular;

public:
    // Конструктор по умолчанию
    Square() : Rectangle(), isRegular(true) {
        cout << "Вызван конструктор по умолчанию класса Square." << endl;
    }

    // Конструктор с параметрами
    Square(const string& c, double side) : Rectangle(c, side, side), isRegular(true) {
        cout << "Вызван конструктор с параметрами класса Square. Длина сторон: " << side << endl;
    }

    // Конструктор копирования
    Square(const Square& other) : Rectangle(other), isRegular(other.isRegular) {
        cout << "Вызван конструктор копирования класса Square." << endl;
    }

    // Деструктор
    ~Square() override {
        cout << "Вызван деструктор класса Square" << endl;
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        cout << "Square Info - Длина сторон: " << getWidth() << ", Цвет: " << getColor()
            << ", Площадь: " << area() << ", Периметр: " << perimeter() << endl;
    }

    // Переопределенный виртуальный метод (из Shape через Rectangle)
    void scale(double factor) override {
        Rectangle::scale(factor); // Вызов метода базового класса
        cout << "К квадрату было применено масштабирование с коэффициентом: "<< factor << endl;
    }

    // Перегруженный метод
    void scale(int factor) {
        Rectangle::scale(static_cast<double>(factor));
        cout << "К квадрату было применено масштабирование с целочисленным коэффициентом: " << factor << endl;
    }
};

// Класс-потомок 5: Ellipse
class Ellipse : public Shape {
private:
    double semiMajorAxis;
    double semiMinorAxis;

public:
    // Конструктор по умолчанию
    Ellipse() : Shape(), semiMajorAxis(2.0), semiMinorAxis(1.0) {
        cout << "Вызван конструктор по умолчания класса Ellipse. Длины полуосей: " << semiMajorAxis << ", " << semiMinorAxis << endl;
    }

    // Конструктор с параметрами
    Ellipse(const string& c, double a, double b) : Shape(c), semiMajorAxis(max(a, b)), semiMinorAxis(min(a, b)) {
        cout << "Вызван конструктор с параметрами класса Ellipse. Длины полуосей: " << semiMajorAxis << ", " << semiMinorAxis << endl;
    }

    // Конструктор копирования
    Ellipse(const Ellipse& other) : Shape(other), semiMajorAxis(other.semiMajorAxis), semiMinorAxis(other.semiMinorAxis) {
        cout << "Вызван конструктор копирования класса Ellipse. Длины полуосей: " << semiMajorAxis << ", " << semiMinorAxis << endl;
    }

    // Деструктор
    ~Ellipse() override {
        cout << "Вызван деструктор класса Ellipse. Длины полуосей: " << semiMajorAxis << ", " << semiMinorAxis << endl;
    }

    // Переопределение виртуальных методов
    double area() const override {
        return M_PI * semiMajorAxis * semiMinorAxis;
    }

    double perimeter() const override {
        // Приближенная формула расчета периметра эллипса
        double h = pow((semiMajorAxis - semiMinorAxis) / (semiMajorAxis + semiMinorAxis), 2);
        return M_PI * (semiMajorAxis + semiMinorAxis) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
    }

    void displayInfo() const override {
        Shape::displayInfo();
        cout << "Ellipse Info - Большая полуось: " << semiMajorAxis
            << ", Малая полуось: " << semiMinorAxis
            << ", Площадь: " << area() << ", Периметр: " << perimeter() << endl;
    }

    // Переопределение виртуального метода scale
    void scale(double factor) override {
        semiMajorAxis *= factor;
        semiMinorAxis *= factor;
        cout << "К эллипсу было применено масштабирование с коэффициентом: " << factor
            << ". Новые длины полуосей: " << semiMajorAxis << ", " << semiMinorAxis << endl;
    }

    // Собственные методы
    double getEccentricity() const { // Рассчет эксцентриситета 
        return sqrt(1 - pow(semiMinorAxis / semiMajorAxis, 2));
    }
};

// Функция для демонстрации полиморфизма
void demonstratePolymorphism(const vector<Shape*>& shapes) {
    cout << "\n=== Демонстрация полиморфизма ===\n";
    for (const auto& shape : shapes) {
        shape->displayInfo();
        cout << "-------------------\n";
    }
}

int main() {
    setlocale(LC_ALL, "Rus"); // Установка русской локали для корректного вывода кириллицы

    cout << "=== Демонстрация работы с фигурами ===\n\n";

    // Демонстрация работы конструкторов
    cout << "--- Создание объектов ---\n";

    Circle circle1; // Конструктор по умолчанию
    Circle circle2("red", 5.0); // Конструктор с параметрами
    Circle circle3(circle2); // Конструктор копирования

    Rectangle rect1("blue", 4.0, 6.0);
    Triangle triangle1("green", 3.0, 4.0, 5.0);
    Square square1("yellow", 4.0);
    Ellipse ellipse1("purple", 5.0, 3.0);

    cout << "\n--- Выше показана работа конструкторов с демонстрацией иерархии вызовов (сначала базовый класс Shape, затем класс-потомок) ---\n\n";

    cout << "\n=== Демонстрация полиморфизма через базовый класс ===\n";

    // Создаем вектор указателей на базовый класс
    vector<Shape*> shapes;

    shapes.push_back(&circle2);
    shapes.push_back(&rect1);
    shapes.push_back(&triangle1);
    shapes.push_back(&square1);
    shapes.push_back(&ellipse1);

    // Демонстрация полиморфного поведения
    demonstratePolymorphism(shapes);

    cout << "\n--- Полиморфизм демонстрируется через вызов виртуального метода displayInfo(). "
        << "Несмотря на то, что имя метода одинаковое, каждый объект выводит свою информацию (радиус для круга, стороны для треугольника и т.д.) ---\n\n";

    cout << "\n=== Демонстрация перегруженных методов ===\n";

    // Демонстрация перегруженных методов Circle
    cout << "Окружность до масштабирования: радиус = " << circle2.getRadius() << endl;
    circle2.scale(2.0); // Перегруженный метод с double
    cout << "Окружность после масштабирования: радиус = " << circle2.getRadius() << endl;
    circle2.scale(2); // Перегруженный метод с int
    cout << "Окружность после целочисленного масштабирования: радиус = " << circle2.getRadius() << endl;

    cout << "\n--- Перегрузка методов показана на примере методов scale() в классе Circle - один принимает double, другой int. "
        << "Работает нужная версия в зависимости от типа аргумента ---\n\n";

    cout << "\n=== Демонстрация виртуального переопределения ===\n";

    // Виртуальное переопределение в Square
    Square square2("orange", 3.0);
    square2.displayInfo();
    square2.scale(2.0); // Вызов переопределенного виртуального метода
    square2.displayInfo();

    cout << "\n--- Виртуальное переопределение показано на примере Square::scale(), который вызывает Rectangle::scale() (родительский метод), "
        << "а затем добавляет свою логику. Это демонстрирует расширение функциональности базового класса в потомке ---\n\n";

    cout << "\n=== Демонстрация работы с динамическим полиморфизмом ===\n";

    // Создаем объекты в куче для демонстрации полиморфизма
    vector<Shape*> dynamicShapes;

    dynamicShapes.push_back(new Circle("cyan", 2.5));
    dynamicShapes.push_back(new Rectangle("magenta", 3.0, 7.0));
    dynamicShapes.push_back(new Triangle("brown", 5.0, 6.0, 7.0));
    dynamicShapes.push_back(new Square("pink", 2.0));
    dynamicShapes.push_back(new Ellipse("violet", 4.0, 2.0));

    cout << "\nДемонстрация полиморфизма с динамическими объектами:\n";
    for (const auto& shape : dynamicShapes) {
        cout << "Площадь: " << shape->area() << ", Периметр: " << shape->perimeter() << endl;
    }

    cout << "\n--- Методы area() и perimeter(), вызываемые через указатель на Shape, выполняют свою логику для каждой фигуры ---\n\n";

    // Проверка статического счетчика
    cout << "\n=== Статистика ===\n";
    cout << "Всего создано фигур: " << Shape::getTotalShapes() << endl;

    // Очистка памяти
    cout << "\n=== Освобождение памяти ===\n";
    for (auto& shape : dynamicShapes) {
        delete shape;
    }

    cout << "\n=== Уничтожение локальных объектов ===\n";
    // Локальные объекты будут уничтожены автоматически при выходе из области видимости

    return 0;
}
