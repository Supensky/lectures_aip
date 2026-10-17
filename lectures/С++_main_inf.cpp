/*
ЛЕКЦИЯ 1
!!! C++ !!!

   auto для переменных, которые мы пока не знаем какого типа будут

namespace foo{
    const int x = 5;
    void t() {}
    namespace bar {
        floar b = 2.2;
    }
}
ПРОСТРАНСТВО ИМЕН
можно использовать:
int main() {
    const int y = foo::x;
    y;
    foo::t();
    foo::bar:b
}

ССЫЛКИ (похоже на указатель, но не является им)
swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

INCLUDE в C++
#include <iostream>
#include <stdint>

void print(const std::string &s){
    std::count << s << std::endl;
}

Ссылка - не полная замена указателей

RANGE FOR
for (объявление переменной : выражение) {
    // тело цикла
}

УПРАВЛЕНИЕ ПАМЯТЬЮ
int* p = new int;
int* q = new int(100);
int* r = new int();
int* s = new int{7}

delete p;
delete q;
delete r;
delete s;

выделение памяти для массивов
int* bar = new int[5]{1, 2, 3, 4, 5};
delete[] bar

выделенте памяти в уже выделенной памяти
char* buffer = new char[1024]
int* pi = new(buffer)
float* pf = new(buffer + sizeof(int)) float(3.14f);
в buffer дополнительно выделяем pi и pf

ОШИБКИ ВЫДЕЛЕНИЯ ПАМЯТИ (исключение)
try {
    while (true) {
        new int(1000000000000000l); //здесь должна быть ошибка, слищком большой объем
    }
} catch (const std::bad_alloc& e) {
    std::cout << e.what() << '\n';
}

nullptr
while (true) {
    new int(1000000000000000l); //здесь должна быть ошибка, слищком большой объем
    if (p == nullptr) {
    std::cout << "Allocarion returned\n";
}

АРГУМЕНТЫ ФУНКЦИЙ ПО УМОЛЧАНИЮ

ПЕРЕГРУЗКА ФУНКЦИЙ
создание одинаковых названий функций с разными агрументами
int add(int a, int b) {
    return a + b;
}

double add(float a, float b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << "\n" // вызов версии int
    srd::cout << add(2.5, 3.7) << "\n" // вызов версии double
}

ограничения на перегрузку функций
1. нельзя создавать новые операторы
2. нельзя переопределять операторы для встроенных типов
3. нельзя менять число аргументов, приоритет и ассоциативность
4. нельзя использовать аргументы по умолчанию

ПОТОКОВЫЙ ВВОД-ВЫВОД

std::cout << std::fixed << std::setprecision(2) << std::numbers::pi << "\n"; // 3.14
std::cout << std::dec << 255 << "\n" // 255

ПОТОКОВЫЙ ВВОД С ПОМОЩЬЮ <<
int main() {
    int age;
    std::string name;
    std::cout << "Введите имя"
    std::getline(std::cin, fullName); // читает строку до \n
}

ПРИВЕДЕНИЕ ТИПОВ
int i = (int)d
int i = static_cast<int>(d) // в основном используем статичсекое

ШАБЛОНЫ
средство обобщенного программирования,
позволяющее описывать функции, классы и переменные без привязки к типам данных или значениям

пример:
template <typename T>
void swap(&T a, T& b) {
    T temp = a;
    a = b
    b = temp
}

// Где-то в коде
int x = 1, y = 2;
swap(x, y)

double q = 1.5, q = 3.7;
swap(p, q);

cppreference.com


Лекция 2
!!! ООП в C++ !!!

ООП - парадигма программирования, в которой программа строится как совокупность взаимодействующих
объектов. Объект объединяет данные (состояние - и методы их обработки).

Наследование - переиспользование кода через расшиерние.

Класс - модель для создания объектов определенного типа, описывающая структуру и определяющая
поведение для работы с этими объектами

Объект - .. воплощение класса.. конкретный экземпляр класса, существующий во время выполнения программы. Обладает:
    состоянием (значиниями набора свойств)
    поведением (методами с помошью которых можно изменить свойства)
    идентичностью (уникальная ссылка)

Члены класса - .. то из чего состоит класс .. поля внутри класса .. общее название для свойств и методов

Пример:
____________________________________________________

class Point2d {
public:
    double x = 0;
    double y = 0;

    void move(double dx, double dy) {
        x += dx;
        y += dx;
    }
    void print() {
        std::cout << "(" << x << ", " << y << ")";
    }
}

int main() {
    Point2d p;
    p.x = 1.0;
    p.y = 2.0;
    p.print(); // (1, 2)
    p.move(-2.0, -2.0);
    p.print(); // (-1, 0)
    return 0;
}
____________________________________________________

Объявление функции в классе,
реализация вне класса:

#include <iostring>
class t{
int exemple(int n);
}
int t::exemple(int n){
return n;
}

слово класс можно определять с помощью слов: class, struct, union.


Разница Public и Private:
В private нельзя обратиться к объекту класса вне функции (p.x - выдаст ошибку)
В public можно пользоваться p.x


enum class Day {
    Monday = 2,
    Tuesday,
    Wednesday,
    ...
    Sunday = 1
};

Day today {Day::Tuesday};



КЛЮЧЕВОЕ СЛОВО this - указатель на объект, для которого этот метод вызван:

Point2d::move(1, 2); - в коде
конвертируется в:
Point2d::move(&p, 1, 2); - по факту
               ^
               |
             this

this->call1()
Point2d&::print() {
    std::cout <<
    ...;
    return *this;
}


ИНИЦИАЛИЗАЦИЯ ЧЛЕНОВ КЛАССА
-----
std::string s1;

std::string s3 = "hello"; // создание объекта типа строка и присваивание ей значение "hello"

std::string s4("hello");  // вызывает инициализирующий конструктор, которой примет указательн на c - строку
// и сделает примерно то же, что и std::string s3 = "hello";

std::string s5{'a'} // иницализация списком

char a[3] = {'a', 'b'};
-----


КОНСТРУКТОР - функция, которая создает значение составного типа.

В ООП конструктор - специальный метод класса который автоматически вызывается при создании
экземпляра этого класса. .. функция которая создает классы ..


Пример:

#include <iostream>
#include <string>

struct Person {
    Person() : m_name("Noname") {} // конструктор Person() вызывает конструктор m_name().

    const std::string& name() { return m_name; }
private:
    std::string m_name;

}

int main() {
    Person a_person;
    std::cout << a_person.name() << std::endl;
    return 0;


ПЕРЕГРУКА КОНСТРУКТОРОВ
Person() {...}
Person(const str, ...) {...}


ПРИМЕР КОПИРУЮЩЕГО КОНСТРУКТОРА
class Buffer {
private:
    int* data;
    size_t size;
public:
    Buffer(size_t size) : size(size), data(new int(size)) { // конструктор
    std::cout << "Создан буфер размером " << size << "\n";
    }

    Buffer() { // деструктор
        delete[] data;
    }

    // конструктор копирования
    Buffer(const Buffer& other) :
        size(other, size),
        data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Копирование\n";
        }
}


ДЕСТРУКТОР - специальный метод класса, который автоматически вызывается при уничтожении объекта
для освобождения занятых ресурсов.


УДАЛЕНИЕ ОБЪЕКТА
class Bufer {
private:
    ...
public:
    ...
    ...
    ~Buffer() {
        delete[] data;
        std::cout << "Буфер уничтожен\n";
    }
    // Конструктор перемещения
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
}


СТАТИЧЕСКИЕ СВОЙСТВА И МЕТОДЫ
#include <iostream>

class User {
public:
    static int userCount; // Статическое свойство (объявление)
    User() {userCount++;} // конструктор (вызывается при создании объекта)
    ~User() {userCount--;} // деструктор (вызывает при удалении объекта)
};
// Определение переменной к инициализации переменной вне класса
int User:userCount = 0;

int main() {
    User u1;
    User u2;
    std::cout << "Активных пользователей: " << User::userCount << std::endl;
    // выведет 2 в этом месте
}


ПРИМЕР СТАТИЧЕСКОГО СВОЙСТВА: ВЫЧИСЛЕНИЕ НА ЭТАПЕ КОМПИЛЯЦИИ
Class Math {
public:
    static constexpr int square(int x) { return x * x; }
};
// static_assert -- проверка условия на этапе компиляции
static_assert(Math::square(5) == 25); // из-за static можно вызывать вне функций

СТАТИЧЕСКИЕ МЕТОДЫ

ЛЕКЦИЯ 3

СТАТИЧЕСКИЕ МЕТОДЫ


ПРИМЕР ИМЕНОВАННЫЙ КОНСТРУКТОР

#include <cmath>
class Point {
    double x_, y_;
    Point(double x, double y) : x_(x), y_(y) {}
public:
    static Point fromPolar(double r, double phi) {
        return Point(r * std::cos(phi), r * std::sin(phi));
    }
};

// Где-то в другом месте программы
auto p = Point::fromPolar(1.0, 0.0);


ПРИМЕР ФАБРИЧНЫЙ МЕТОД

#include <string>

// Базовый класс
class Shape {
public:
    // Нужен для того, чтобы при удалении по указателю на базовый класс
    // вызывался деструктор дочернего класса, если он есть
    virtual ~Shape() = default;
};

class Circle : public Shape()
class Square : public Shape()

class ShapeFactory {
public:
    static Shape* create(const std::string& type) {
        if (type == "circle") return new Circle();
        return new Square()
    }
};

// Где-то в коде
Shape* s = ShapeFactory::create("circle");
// ...
delete s;


ПРИМЕР СИНГЛТОН

class Config {
    Config() = default; // Приватный конструктор по умолчанию
public:
    static Config& instance() {
        static Config cfg;
        return cfg;
    }
    // Какой-то код
};

// Где-то в коде
auto& cfg = Config::instance();

auto config = Config::instance(); // Ссылка на тот же объект


ПРИМЕР КОЛЛБЭК

#include <iostream>

// Класс-обработчик событий
class Handler {
public:
    static void onEvent(int value) {
        std::cout << "[Handler] получено значение " << value << "\n";
    }
};

// Функция, принимающая коллбэк (указатель на функцию)
void process(int data, void(*callback)(int)) {
    std::cout << "Обрабатываю данные: " << data << "\n";
    // ... какая-то работа ...

    // Вызываем коллбэк
    callback(data * 2);
}

int main() {
     // Передаем статические метод как коллбэк
     process(21, &Handler::onEvent);

НАСЛЕДОВАНИЕ В ООП


ПРИМЕР НАСЛЕДОВАНИЯ, ОСНОВАННОГО НА КЛАССАХ

class Figure {};

class Square : public Figure {
    double side_;
public:
    explicit Square(double side) : side_(side) {}
};

class Circle : public Figure {
    double radius_;
public:
    explicit Circle(double radius) : radius_(radius) {}
};

int main() {
    Square s(5.0);
    Circle c(3.0);
}

Наследование - выражение отношения "является"
Композиция - сочетание с владением, когда времена жизни совпадают (исчезает класс, исчезают дочерние)
Агрегация - сочетание без владения (исчезает класс, дочерние остаются)

ПРИМЕР КОМПОЗИЦИИ

#include <iostream>
#include <stdexcept>

class Fraction {
public:
    Fraction(int num, int den) : num_(num), den_(den) {
        if (den_ == 0)
            throw std::invalid_argument("denominator cannot be zero");
    }
    void print() const {
        std::cout << num_ << "/" << den_ << "\n";
    }
private:
    // Части -- приватные вложенные классы, снаружи недоступны
    struct Numerator {
        int value;
        Numerator(int v) : value(v) {}
    };
    struct Denominator {
        int value;
        Denominator(int v) : value(v) {}
    };
    Numerator num_;
    Denumerator den_;

int main() {
    Fraction f(3, 4);
    f.print(); // 3/4
}

ПРИМЕР АГРЕГАЦИИ

#include <iostream>
#include <vector>

class Element {
public:
    explicit Element(int value) : value_(value) {}
    int value() const { return value_; }
private:
    int value_;
};

class Set {
public:
    void insert(Element* e) { elements_.push_back(e); } // агрегация: не владеем
    void print() const {
        std::cout << "{";
        for (const Element* e : elements_)
            std::cout << e->value() << " ";
        std::cout << "}\n";
    }
private:
    std::vector<Element*> elements_; // ссылки на внешние объекты
};


НАСЛЕДОВАНИЕ КОНСТРУКТОРОВ

struct Derived : Base {
    Derived(int x) : Base(x) {}
    Derived(int x, int y) : Base(x, y) {}
};


ДРУЗЬЯ КЛАССА - механизм C++ позволяющий функции или другому классу получить
доступ к членам класса, объявленным как private или protected, как если бы они были собственными.

ПРИМЕР ДРУЖЕСТВЕННОЙ ФУНКЦИИ

#include <iostream>
#include <cmath>

class Point {
private:
    double x, y;
public:
    Point(double x, double y) : x(x), y(y) {}
    friend double distance(const Point& a, const Point& b);
};

double distance() { ... }

int main() {
    Point p1(0, 0), p2(3, 4);
    std::cout << distance(p1, p2); // 5
}

ДРУЖЕСТВЕННЫЙ КЛАСС

class Storage {
private:
    int secret = 42;
    friend class Inspector;
};

class Inspector {
public:
    void show(const Storage& s) {
        std::cout << s.secret; // доступ разрешен
    }
};


ПЕРЕГРУЗКА << С ГЕТТЕРАМИ

class Point {
    double x_, y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}
    double x() const { return x_; }
    double y() const { return y_; }
};

std::ostream& operator<<(std::cout& os, const Point& p) {
    return os << "(" << p.x() << ", " << p.y() << ")";
}

int main() {
    Point p(1.5, 2.5);
    std::cout << p << '\n'; // (1.5, 2.5)


ВИРТУАЛЬНЫЙ МЕТОД
метод класса, который может быть переопределен в производных классах.
Это называется динамическим связыванием.

ПРИМЕР ВИРТУАЛЬНОГО МЕТОДА

#include <iostream>

class Function {
public:
    virtual double evaluate(double x) const = 0; // (1) // виртуальные функции
    virtual ~Function() = default; // (2)
};

class Quadratic : public Function {
public:
    double evaluate(double x) const override { // (3) // переписываем метод в новом классе Quadratic
        return x * x;
    }
};


АЛГЕБРАИЧЕСКИЙ ТИП ДАННЫХ
составной тип, значение которого строится одним из нескольких конструкторов,
и каждый конструктор содержит набор значений других типов.


ЭМУЛЯЦИЯ АЛГЕБРАИЧЕСКОГО ТИПА ДАННЫХ В С++

constespr double kPi = = 2.0 * std::asin(1.0);

class Shape {
public:
    virtual double perimeter() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
    double width_;
    double height_;
public:
    Rectangle(double width, double height)
        : width_(width), height_(height) {}

        double perimeter() const override {
            return 2 * (width_ + height_);
        }
    }
}

int main() {
    std::vector<std::unique_pt<Shape>> shapes;

    shapes.pushback(std::make_unique<Rectangle>(3.0, 4.0));
    std::cout << shape->perimeter() << '\n';

    return 0;
}


ИНТЕРФЕЙС
абстрактный тип, который задает набор операций, но не их реализацию

ПРИМЕР ИНТЕРФЕЙСА

struct IEncoder { // интерфейс
    virtual std::string encode(const std::string& s) const = 0;
    virtual ~IEncoder() = default;
};

struct Upper : IEncoder {
    std::string encode(const std::string& s) const override {
        std::string r = s;
        for (char& c : r) c = std::toupper(c);
        return r;
    }
};

struct Reverse : IEncoder {
    std::string encode(const std::string& s) const override {
        return std::string(s.rbegin(), s.rend());
    }
};

std::string encode {
    ...
    }



*/