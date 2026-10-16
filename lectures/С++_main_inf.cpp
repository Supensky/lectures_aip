/*
Лекция 1
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

*/